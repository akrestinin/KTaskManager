#include "k_task_manager.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief
 *
 */
typedef struct KTaskManagerTask {
    KTaskManager_TaskClbk_t Clbk;
    uint32_t                Period;
    uint32_t                LastRun;
} KTaskManager_Task_t;

/**
 * @brief
 *
 */
typedef struct KTaskManager {
    uint32_t                MaxTaskNum;
    uint32_t                RegTaskNum;
    KTaskManager_Task_t*    pTasks;
    KTaskManager_TimeFunc_t GetTime;
} KTaskManager_t;

KTaskManager_Handle_t KTaskManager_Create(uint32_t                maxTaskNum,
                                          KTaskManager_TimeFunc_t getTimeFunc) {
    assert(maxTaskNum != 0);
    assert(getTimeFunc != NULL);

    KTaskManager_t*      pNewTaskManager = malloc(sizeof(KTaskManager_t));
    KTaskManager_Task_t* pNewTasksArr =
        malloc(sizeof(KTaskManager_Task_t) * maxTaskNum);
    if (pNewTaskManager == NULL || pNewTasksArr == NULL)
        return NULL;

    pNewTaskManager->MaxTaskNum = maxTaskNum;
    pNewTaskManager->RegTaskNum = 0;
    pNewTaskManager->pTasks     = pNewTasksArr;
    memset(
        pNewTaskManager->pTasks, 0, sizeof(KTaskManager_Task_t) * maxTaskNum);
    pNewTaskManager->GetTime = getTimeFunc;

    return pNewTaskManager;
}

KTaskManager_Handle_t
KTaskManager_CreateStatic(KTaskManager_Static_t*     pTaskManagerStorage,
                          KTaskManager_StaticTask_t* pTaskStorage,
                          uint32_t                   maxTaskNum,
                          KTaskManager_TimeFunc_t    getTimeFunc) {
    assert(pTaskManagerStorage != NULL);
    assert(pTaskStorage != NULL);
    assert(maxTaskNum != 0);
    assert(getTimeFunc != NULL);
    assert(sizeof(KTaskManager_t) == sizeof(KTaskManager_Static_t));
    assert(sizeof(KTaskManager_Task_t) == sizeof(KTaskManager_StaticTask_t));

    KTaskManager_t* pNewTaskManager = (KTaskManager_t*)pTaskManagerStorage;

    pNewTaskManager->MaxTaskNum     = maxTaskNum;
    pNewTaskManager->RegTaskNum     = 0;
    pNewTaskManager->pTasks         = (KTaskManager_Task_t*)pTaskStorage;
    memset(
        pNewTaskManager->pTasks, 0, sizeof(KTaskManager_Task_t) * maxTaskNum);
    pNewTaskManager->GetTime = getTimeFunc;

    return pNewTaskManager;
}

int KTaskManager_TaskRegister(KTaskManager_Handle_t   pSelf,
                              KTaskManager_TaskClbk_t taskClbk,
                              uint32_t                period) {
    assert(pSelf != NULL);
    assert(taskClbk != NULL);
    assert(period != 0);

    if (pSelf->RegTaskNum >= pSelf->MaxTaskNum)
        return -1;

    pSelf->pTasks[pSelf->RegTaskNum].Clbk    = taskClbk;
    pSelf->pTasks[pSelf->RegTaskNum].Period  = period;
    pSelf->pTasks[pSelf->RegTaskNum].LastRun = pSelf->GetTime();
    pSelf->RegTaskNum++;

    return pSelf->RegTaskNum - 1;
}

bool KTaskManager_TaskDelete(KTaskManager_Handle_t pSelf, uint32_t id) {
    assert(pSelf != NULL);

    if (id < pSelf->RegTaskNum)
        return false;

    pSelf->pTasks[id].Clbk    = NULL;
    pSelf->pTasks[id].Period  = 0;
    pSelf->pTasks[id].LastRun = 0;
    pSelf->RegTaskNum--;

    return true;
}

uint32_t KTaskManager_GetMaxTaskNum(KTaskManager_Handle_t pSelf) {
    assert(pSelf != NULL);

    return pSelf->MaxTaskNum;
}

uint32_t KTaskManager_GetRegTaskNum(KTaskManager_Handle_t pSelf) {
    assert(pSelf != NULL);

    return pSelf->RegTaskNum;
}

void KTaskManager_Process(KTaskManager_Handle_t pSelf) {
    assert(pSelf != NULL);

    for (uint32_t i = 0; i < pSelf->RegTaskNum; i++) {
        KTaskManager_Task_t* pTask = &pSelf->pTasks[i];
        if (pSelf->GetTime() - pTask->LastRun >= pTask->Period) {
            pTask->Clbk();
            pTask->LastRun = pSelf->GetTime();
        }
    }
}

void KTaskManager_Destroy(KTaskManager_Handle_t pSelf) {
    assert(pSelf != NULL);

    free(pSelf->pTasks);
    free(pSelf);
    pSelf = NULL;
}

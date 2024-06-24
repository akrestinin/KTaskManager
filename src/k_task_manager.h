/**
 * @file k_task_manager.h
 * @version 1.0
 * @author Krestinin Aleksandr (krestinin.al99@gmail.com)
 * @brief
 */

#ifndef K_TASK_MANAGER_H
#define K_TASK_MANAGER_H

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

/**
 * @brief
 *
 */
typedef void (*KTaskManager_TaskClbk_t)(void);

/**
 * @brief
 *
 */
typedef long (*KTaskManager_TimeFunc_t)(void);

/**
 * @brief
 *
 */
typedef struct KTaskManager KTaskManager_t;

/**
 * @brief
 *
 */
typedef KTaskManager_t* KTaskManager_Handle_t;

typedef struct {
    void*    Dummy0;
    uint32_t Dummy1;
    uint32_t Dummy2;
} KTaskManager_StaticTask_t;

typedef struct {
    uint32_t Dummy0;
    uint32_t Dummy1;
    void*    Dummy2;
    void*    Dummy3;
} KTaskManager_Static_t;

/**
 * @brief
 *
 * @param maxTaskNum
 * @return KTaskManager_Handle_t
 */
KTaskManager_Handle_t KTaskManager_Create(uint32_t                maxTaskNum,
                                          KTaskManager_TimeFunc_t getTimeFunc);

/**
 * @brief
 *
 * @param pTaskManagerStorage
 * @param pTaskStorage
 * @param maxTaskNum
 * @param getTimeFunc
 * @return KTaskManager_Handle_t
 */
KTaskManager_Handle_t
KTaskManager_CreateStatic(KTaskManager_Static_t*     pTaskManagerStorage,
                          KTaskManager_StaticTask_t* pTaskStorage,
                          uint32_t                   maxTaskNum,
                          KTaskManager_TimeFunc_t    getTimeFunc);

/**
 * @brief
 *
 * @param pSelf
 * @param taskClbk
 * @param period
 * @return int
 */
int KTaskManager_TaskRegister(KTaskManager_Handle_t   pSelf,
                              KTaskManager_TaskClbk_t taskClbk,
                              uint32_t                period);

/**
 * @brief
 *
 * @param pSelf
 * @param id
 * @return true
 * @return false
 */
bool KTaskManager_TaskDelete(KTaskManager_Handle_t pSelf, uint32_t id);

/**
 * @brief
 *
 * @param pSelf
 * @return uint32_t
 */
uint32_t KTaskManager_GetMaxTaskNum(KTaskManager_Handle_t pSelf);

/**
 * @brief
 *
 * @param pSelf
 * @return uint32_t
 */
uint32_t KTaskManager_GetRegTaskNum(KTaskManager_Handle_t pSelf);

/**
 * @brief
 *
 * @param pSelf
 */
void KTaskManager_Process(KTaskManager_Handle_t pSelf);

/**
 * @brief
 *
 * @param pSelf
 */
void KTaskManager_Destroy(KTaskManager_Handle_t pSelf);

#endif /* K_TASK_MANAGER_H */

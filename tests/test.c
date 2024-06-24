#include "k_task_manager.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define TASKS_NUM              2
#define FIRST_TASK_PERIOD_SEC  1
#define SECOND_TASK_PERIOD_SEC 5

#define STYLE_SYS(s)           ("\033[36m" s "\033[0m")
#define STYLE_SUCCESS(s)       ("\033[32m" s "\033[0m")
#define STYLE_ERROR(s)         ("\033[31m" s "\033[0m")

void task1(void) {
    printf("Task 1 triggered. Period [%d] second\r\n", FIRST_TASK_PERIOD_SEC);
}

void task2(void) {
    printf("Task 2 triggered. Period [%d] seconds\r\n", SECOND_TASK_PERIOD_SEC);
}

long MygetTime(void) {
    struct timeval now;
    gettimeofday(&now, NULL);

    return now.tv_sec;
}

int main(void) {
    KTaskManager_Static_t     tmStorage;
    KTaskManager_StaticTask_t tmTaskStorge[TASKS_NUM];
    KTaskManager_Handle_t     hTaskManager = KTaskManager_CreateStatic(
        &tmStorage, tmTaskStorge, TASKS_NUM, MygetTime);
    KTaskManager_TaskRegister(hTaskManager, task1, FIRST_TASK_PERIOD_SEC);
    KTaskManager_TaskRegister(hTaskManager, task2, SECOND_TASK_PERIOD_SEC);

    while (true) {
        KTaskManager_Process(hTaskManager);
    }

    KTaskManager_Destroy(hTaskManager);
    return 0;
}

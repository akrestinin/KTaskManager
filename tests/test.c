#include "k_task_manager.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST_CYCLES      1000000

#define STYLE_SYS(s)     ("\033[36m" s "\033[0m")
#define STYLE_SUCCESS(s) ("\033[32m" s "\033[0m")
#define STYLE_ERROR(s)   ("\033[31m" s "\033[0m")

static void PrintResult(bool result) {
    if (result)
        printf(STYLE_SUCCESS("SUCCESS\r\n"));
    else
        printf(STYLE_ERROR("FAILED\r\n"));
}

int main(void) { return 0; }

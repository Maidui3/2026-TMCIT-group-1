/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief RPG main sorce
 * @version 1.0
 * @date 2026-08-16
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <SDL3/SDL.h>
// #define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "rpg.h"
#define DEBUG_MODE

/*build ファイルは消さないように　cmakeの構成がめっちゃ重い*/

int main(int argc, char* argv[])
{
    printf(" \r\n");
    printf("SDL Version 3.4.14\r\n");
    printf("Game Version 1.0\r\n");
    printf("\r\n");
    printf("MODE -> ");

#ifdef DEBUG_MODE
    printf("DEBUG\r\n");
#else
    printf("RELEASE\r\n");
#endif

    if (RPG_Init() != RPG_Init_OK) {
        printf("setup error");
        return 1;
    }

    while (1) {
        if (RPG_Loop() != RPG_Loop_OK) {
            printf("loop error");
            return 1;
        }

#ifdef DEBUG_MODE
        return 0;
#endif
    }
}

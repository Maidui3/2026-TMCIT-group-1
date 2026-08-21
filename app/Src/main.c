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
#include <SDL3_image/SDL_image.h>
// #define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "rpg.h"
#define DEBUG_MODE

int main(int argc, char* argv[])
{
    printf("\r\n");
    printf("MODE -> ");

#ifdef DEBUG_MODE
    printf("DEBUG\r\n");
#else
    printf("RELEASE\r\n");
#endif

    if (RPG_Init() != RPG_OK) {
        printf(SDL_GetError());
        printf("\r\n");
        RPG_Quit();
        printf("setup error");
        printf("\r\n");
        return 1;
    }

    while (1) {
        if (RPG_Loop() != RPG_OK) {
            printf(SDL_GetError());
            printf("\r\n");
            RPG_Quit();
            printf("loop error");
            return 1;
        }

        SDL_Delay(1000);

#ifdef DEBUG_MODE
        break;
#endif
    }

    RPG_Quit();

    return 0;
}

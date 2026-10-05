/**
 * @file rpg.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _RPG_H_
#define _RPG_H_

#define Application_NAME "jyouhou_kadai"
#include "SDL3/SDL_stdinc.h"

typedef enum {
    RPG_OK,
    RPG_Error,
} RPG_State_t;

typedef struct {
    Uint8 R, G, B;
} back_light_t;

typedef struct {
    char bit_map[60][96];
} bit_map_t;

RPG_State_t RPG_Init();
RPG_State_t RPG_Loop();
RPG_State_t RPG_Quit();

#endif

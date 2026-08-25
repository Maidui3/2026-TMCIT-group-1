/**
 * @file rpg_texture_loader.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _RPG_TEXTURE_LOADER
#define _RPG_TEXTURE_LOADER

#include "rpg.h"
#include "rpg_window_render.h"

typedef enum {
    MAP_1,
    MAP_2,
    MAP_3,
    chara,
    enamy1,
    enamy2,
    enamy3,
    enamy4,
} texture_map_t;

RPG_State_t RPG_Texture_Loader(SDL_Renderer** renderer, RPG_Win_Render_Handler_t* x_Render, texture_map_t map);
RPG_State_t RPG_Texture_Loader_Qnit(RPG_Win_Render_Handler_t* x_Render);
RPG_State_t RPG_Texture_Loader_Error();

#endif

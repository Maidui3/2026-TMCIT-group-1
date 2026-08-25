/**
 * @file rpg_texture_render.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _RPG_TEXTURE_RENDER
#define _RPG_TEXTURE_RENDER

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

#include "rpg.h"

typedef struct {
    SDL_Texture* texture;
    SDL_FRect src;
    SDL_FRect src_main;
    SDL_Surface* surface;
    int window_x_size;
    int window_y_size;
} RPG_Win_Render_Handler_t;

RPG_State_t RPG_Window_Render_Init(SDL_Renderer* renderer, SDL_Window* window, back_light_t* back_light);
RPG_State_t RPG_Window_Render_main_Upadte(SDL_Renderer* renderer, RPG_Win_Render_Handler_t* x_Render);
RPG_State_t RPG_Window_Render_back_Update(SDL_Renderer* renderer, RPG_Win_Render_Handler_t* x_Render);
RPG_State_t RPG_Window_Render_Qnit(SDL_Renderer* renderer);
RPG_State_t RPG_Window_Render_Error();

#endif

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

typedef enum {
    RPG_Render_OK,
    RPG_Render_Error,
} RPG_Texture_Render_t;

typedef struct {
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int window_x_size;
    int window_y_size;
    const char* pass;
} RPG_Win_Render_Handler_t;

RPG_Texture_Render_t RPG_Window_Render_Init(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window);
RPG_Texture_Render_t RPG_Window_Render_Update(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window);
RPG_Texture_Render_t RPG_Window_Render_Qnit(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window);
RPG_Texture_Render_t RPG_Window_Render_Error();

#endif
/***
 * robo-con
 * RPG
 * ESC
 * Mlink
 * c/c++ CPU
 *
 */
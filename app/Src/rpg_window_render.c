/**
 * @file rpg_texture_render.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "rpg_window_render.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

RPG_Texture_Render_t RPG_Window_Render_Init(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window)
{
    if (!SDL_IsMainThread()) {
        return RPG_Window_Render_Error();
    }

    x_Render->renderer = SDL_CreateRenderer(window, NULL);
    if (x_Render->renderer == NULL) {
        return RPG_Window_Render_Error();
    }

    x_Render->texture = SDL_CreateTexture(x_Render->renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_TARGET, 100, 100);
    if (x_Render->texture == NULL) {
        return RPG_Window_Render_Error();
    }

    return RPG_Render_OK;
}

RPG_Texture_Render_t RPG_Window_Render_Update(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window)
{
    return RPG_Render_OK;
}

RPG_Texture_Render_t RPG_Window_Render_Qnit(RPG_Win_Render_Handler_t* x_Render, SDL_Window* window)
{
    SDL_DestroyRenderer(x_Render->renderer);

    return RPG_Render_OK;
}

RPG_Texture_Render_t RPG_Window_Render_Error()
{
    printf(SDL_GetError());
    printf("\r\n");
    printf("render error");
    printf("\r\n");

    return RPG_Render_Error;
}

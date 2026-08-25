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

RPG_State_t RPG_Window_Render_Init(SDL_Renderer* renderer, SDL_Window* window, back_light_t* back_light)
{
    if (!SDL_IsMainThread()) {
        return RPG_Window_Render_Error();
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == NULL) {
        return RPG_Window_Render_Error();
    }

    if (!SDL_SetRenderDrawColor(renderer, back_light->R, back_light->G, back_light->B, SDL_ALPHA_OPAQUE)) {
        return RPG_Window_Render_Error();
    }
    if (!SDL_RenderClear(renderer)) {
        return RPG_Window_Render_Error();
    }
    SDL_RenderPresent(renderer);

    return RPG_OK;
}

RPG_State_t RPG_Window_Render_main_Upadte(SDL_Renderer* renderer, RPG_Win_Render_Handler_t* x_Render)
{
    SDL_RenderTexture(renderer, x_Render->texture, NULL, &x_Render->src_main);

    return RPG_OK;
}

RPG_State_t RPG_Window_Render_back_Update(SDL_Renderer* renderer, RPG_Win_Render_Handler_t* x_Render)
{
    SDL_RenderTexture(renderer, x_Render->texture, &x_Render->src, NULL);
    SDL_RenderPresent(renderer);

    return RPG_OK;
}

RPG_State_t RPG_Window_Render_Qnit(SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    return RPG_OK;
}

RPG_State_t RPG_Window_Render_Error()
{
    printf("render error");
    printf("\r\n");
    return RPG_Error;
}

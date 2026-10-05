/**
 * @file rpg.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-21
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>
//

#include "rpg.h"
#include "rpg_texture_loader.h"
#include "rpg_window_render.h"

#define RPG_Game_Version 1.0f
#define RPG_texture_num  1

void version();
SDL_Window* window;

SDL_Renderer* renderer;
RPG_Win_Render_Handler_t back_renderer;
RPG_Win_Render_Handler_t charactor_renderer;

back_light_t back_light = {0, 0, 0};
const bool* key;

uint64_t last_tick_render;
uint64_t last_tick_key;

bit_map_t map_border;

RPG_State_t RPG_Init()
{
    version();

    if (!SDL_InitSubSystem((SDL_InitFlags)(SDL_INIT_VIDEO | SDL_INIT_EVENTS))) {
        return RPG_Error;
    }
    /*SDL初期化*/

    window = SDL_CreateWindow(Application_NAME, 100, 100, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        return RPG_Error;
    }
    /*ウィンドウを作成*/

    if (!SDL_GetWindowSize(window, &back_renderer.window_x_size, &back_renderer.window_y_size)) {
        return RPG_Error;
    }
    /*ウィンドウの縦横のサイズを取得*/
    printf("window x size %d \r\n", back_renderer.window_x_size);
    printf("window y size %d \r\n", back_renderer.window_y_size);

    back_light.R = 0x00;
    back_light.G = 0x00;
    back_light.B = 0x00;

    if (RPG_Window_Render_Init(&renderer, window, &back_light) != RPG_OK) {
        return RPG_Error;
    }

    if (RPG_Texture_Loader(&renderer, &back_renderer, MAP_1) != RPG_OK) {
        return RPG_Error;
    }

    if (RPG_Texture_Loader(&renderer, &charactor_renderer, chara) != RPG_OK) {
        return RPG_Error;
    }

    back_renderer.src.x = 0;
    back_renderer.src.y = 0;
    back_renderer.src.w = back_renderer.surface->w / 4;
    back_renderer.src.h = back_renderer.surface->h / 4;

    charactor_renderer.src.x = 0;
    charactor_renderer.src.y = 0;
    charactor_renderer.src.w = 270;
    charactor_renderer.src.h = 270;

    SDL_SetTextureScaleMode(back_renderer.texture, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(charactor_renderer.texture, SDL_SCALEMODE_NEAREST);

    key = SDL_GetKeyboardState(NULL);

    if (RPG_Map_Loader(&map_border, MAP_1) != RPG_OK) {
        return RPG_Error;
    }

    return RPG_OK;
}

#define character_speed_X 15.0f
#define character_speed_Y 10.0f
#define back_speed_X      0.8f
#define back_speed_Y      1.0f
#define character_offset  100.0f
#define Boarder_X         (float)(back_renderer.window_x_size) * 0.2f
#define Boarder_Y         (float)(back_renderer.window_y_size) * 0.15f

#define NO_MOVE '-'
#define ENEMY   'A'
#define MOVE    ' '

#define YP 20.0f

RPG_State_t RPG_Loop()
{
    if (SDL_GetTicks() - last_tick_key >= 10) {
        if (key[SDL_SCANCODE_W]) {
            charactor_renderer.src.y -= character_speed_Y;
            if (Boarder_Y >= charactor_renderer.src.y) {
                charactor_renderer.src.y += character_speed_Y;
                back_renderer.src.y -= back_speed_Y;
                if (back_renderer.src.y <= 0) {
                    back_renderer.src.y += back_speed_Y;
                } else {
                    if (map_border.bit_map[(uint32_t)((back_renderer.src.y) / YP)][(uint32_t)((back_renderer.src.x) / YP)] == NO_MOVE) {
                        back_renderer.src.y += back_speed_Y;
                    }
                }
            } else {
                if (map_border.bit_map[(uint32_t)((back_renderer.src.y) / YP)][(uint32_t)((back_renderer.src.x) / YP)] == NO_MOVE) {
                    charactor_renderer.src.y += character_speed_Y;
                }
            }
        } else if (key[SDL_SCANCODE_S]) {
            charactor_renderer.src.y += character_speed_Y;
            if (back_renderer.window_y_size - character_offset - Boarder_Y <= charactor_renderer.src.y) {
                charactor_renderer.src.y -= character_speed_Y;
                back_renderer.src.y += back_speed_Y;
                if (back_renderer.src.y >= back_renderer.surface->h / 1.4f) {
                    back_renderer.src.y -= back_speed_Y;
                } else {
                    if (map_border.bit_map[(uint32_t)((back_renderer.src.y) / YP)][(uint32_t)((back_renderer.src.x) / YP)] == NO_MOVE) {
                        back_renderer.src.y -= back_speed_Y;
                    }
                }
            } else {
                if (map_border.bit_map[(uint32_t)((back_renderer.src.y) / YP)][(uint32_t)((back_renderer.src.x) / YP)] == NO_MOVE) {
                    charactor_renderer.src.y -= character_speed_Y;
                }
            }
        }
        if (key[SDL_SCANCODE_A]) {
            charactor_renderer.src.x -= character_speed_X;
            if (Boarder_X >= charactor_renderer.src.x) {
                charactor_renderer.src.x += character_speed_X;
                back_renderer.src.x -= back_speed_X;
                if (back_renderer.src.x <= 0) {
                    back_renderer.src.x += back_speed_X;
                }
            }
        } else if (key[SDL_SCANCODE_D]) {
            charactor_renderer.src.x += character_speed_X;
            if (back_renderer.window_x_size - character_offset - Boarder_X <= charactor_renderer.src.x) {
                charactor_renderer.src.x -= character_speed_X;
                back_renderer.src.x += back_speed_X;
                if (back_renderer.src.x >= back_renderer.surface->w / 1.4f) {
                    back_renderer.src.x -= back_speed_X;
                }
            }
        }
        last_tick_key = SDL_GetTicks();
    }

    RPG_Window_Render_back_Update(&renderer, &back_renderer);
    RPG_Window_Render_main_Upadte(&renderer, &charactor_renderer);
    SDL_RenderPresent(renderer);

    return RPG_OK;
}

RPG_State_t RPG_Quit()
{
    RPG_Window_Render_Qnit(&renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return RPG_OK;
}

void version()
{
    printf("\r\n");
    printf("Game Version %.2f ...\r\n", RPG_Game_Version);

    const int sdl_library_version  = SDL_GetVersion();
    const int sdl_compiled_version = SDL_VERSION;

    printf(
        "SDL Library Version %d.%d.%d ...\r\n",
        SDL_VERSIONNUM_MAJOR(sdl_library_version),
        SDL_VERSIONNUM_MINOR(sdl_library_version),
        SDL_VERSIONNUM_MICRO(sdl_library_version)
    );

    printf(
        "SDL Compiled Version %d.%d.%d ...\r\n",
        SDL_VERSIONNUM_MAJOR(sdl_compiled_version),
        SDL_VERSIONNUM_MINOR(sdl_compiled_version),
        SDL_VERSIONNUM_MICRO(sdl_compiled_version)
    );

    printf(SDL_GetRevision());
    printf("\r\n");

    printf("\r\n");
}
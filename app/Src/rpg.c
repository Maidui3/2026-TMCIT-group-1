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
RPG_Win_Render_Handler_t render_handle;

// texture = IMG_LoadGPUTexture(deveice, copypass, "texture/Copilot_20260821_173248.png", &window_x_size, &window_y_size);
// if (texture == NULL) {
//     return RPG_Error;
// }
//
// opened_texture_num++;
// printf("Open texture file %d/%d", opened_texture_num, RPG_texture_num);

RPG_State_t RPG_Init()
{
    version();

    if (!SDL_InitSubSystem(((SDL_InitFlags)SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))) {
        return RPG_Error;
    }
    /*SDL初期化*/

    window = SDL_CreateWindow(Application_NAME, 100, 100, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        return RPG_Error;
    }
    /*ウィンドウを作成*/

    if (!SDL_GetWindowSize(window, &render_handle.window_x_size, &render_handle.window_y_size)) {
        return RPG_Error;
    }
    /*ウィンドウの縦横のサイズを取得*/
    printf("window x size %d \r\n", render_handle.window_x_size);
    printf("window y size %d \r\n", render_handle.window_y_size);

    if (RPG_Window_Render_Init(&render_handle, window) != RPG_OK) {
        return RPG_Error;
    }

    printf("\r\n");
    return RPG_OK;
}

RPG_State_t RPG_Loop()
{
    if (RPG_Window_Render_Update(&render_handle, window) != RPG_Render_OK) {
        return RPG_Error;
    }

    return RPG_OK;
}

RPG_State_t RPG_Quit()
{
    RPG_Window_Render_Qnit(&render_handle, window);
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

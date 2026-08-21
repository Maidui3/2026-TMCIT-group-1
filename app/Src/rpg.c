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

#define RPG_Game_Version 1.0f
#define RPG_texture_num  1

void version();
RPG_State_t SDL_SetUp_GPU();
SDL_Window* window                    = NULL;
SDL_Renderer* renderer                = NULL;
SDL_GPUDevice* gpu_deveice            = NULL;
SDL_IOStream* iostream_world          = NULL;
SDL_GPUCommandBuffer* gpu_command_buf = NULL;
SDL_GPUTexture* gpu_texture           = NULL;
SDL_GPUCopyPass* gpu_copy_pass        = NULL;
int window_x_size                     = 0;
int window_y_size                     = 0;
int opened_texture_num                = 0;

RPG_State_t SDL_SetUp_GPU()
{
    renderer = SDL_CreateGPURenderer(gpu_deveice, window);
    if (renderer == NULL) {
        return RPG_Error;
    }

    gpu_deveice = SDL_GetGPURendererDevice(renderer);
    if (gpu_deveice == NULL) {
        return RPG_Error;
    }

    gpu_command_buf = SDL_AcquireGPUCommandBuffer(gpu_deveice);
    if (gpu_command_buf == NULL) {
        return RPG_Error;
    }

    gpu_copy_pass = SDL_BeginGPUCopyPass(gpu_command_buf);
    if (gpu_copy_pass == NULL) {
        return RPG_Error;
    }

    gpu_texture =
        IMG_LoadGPUTexture(gpu_deveice, gpu_copy_pass, "../../texture/Copilot_20260821_173248.png", &window_x_size, &window_y_size);
    if (gpu_texture == NULL) {
        return RPG_Error;
    }

    opened_texture_num++;
    printf("Open texture file %d/%d", opened_texture_num, RPG_texture_num);

    if (!SDL_SubmitGPUCommandBuffer(gpu_command_buf)) {
        return RPG_Error;
    }

    return RPG_OK;
}

RPG_State_t RPG_Init()
{
    version();

    if (!SDL_InitSubSystem(((SDL_InitFlags)SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS))) {
        return RPG_Error;
    }

    window = SDL_CreateWindow(Application_NAME, 100, 100, SDL_WINDOW_FULLSCREEN);
    if (window == NULL) {
        return RPG_Error;
    }

    if (!SDL_GetWindowSize(window, &window_x_size, &window_y_size)) {
        return RPG_Error;
    }
    printf("window x size %d \r\n", window_x_size);
    printf("window y size %d \r\n", window_y_size);

    if (SDL_SetUp_GPU() != RPG_OK) {
        return RPG_Error;
    }

    printf("\r\n");
    return RPG_OK;
}

RPG_State_t RPG_Loop()
{
    return RPG_OK;
}

RPG_State_t RPG_Quit()
{
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

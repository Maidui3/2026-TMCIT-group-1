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

typedef enum {
    RPG_Loader_OK,
    RPG_Loader_Error,
} RPG_Texture_Loader_t;

RPG_Texture_Loader_t RPG_Texture_Loader_Init();
RPG_Texture_Loader_t RPG_Texture_Loader_Qnit();

#endif

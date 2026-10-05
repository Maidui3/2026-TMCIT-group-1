/**
 * @file rpg_texture_loader.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-08-22
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "rpg_texture_loader.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <stdio.h>

#include "rpg_window_render.h"

RPG_State_t RPG_Texture_Loader(SDL_Renderer** renderer, RPG_Win_Render_Handler_t* x_Render, texture_map_t map)
{
    SDL_IOStream* iostream;
    bool png_or_jpg;

    switch (map) {
        case MAP_1:
            iostream   = SDL_IOFromFile("texture/field-map-for-dungeon-exploration-pixel-art-style1.jpg", "r");
            png_or_jpg = true;
            break;

        case MAP_2:
            iostream   = SDL_IOFromFile("texture/field-map-for-dungeon-exploration-pixel-art-style2.jpg", "r");
            png_or_jpg = true;
            break;

        case MAP_3:
            iostream   = SDL_IOFromFile("texture/field-map-for-dungeon-exploration-pixel-art-style4.jpg", "r");
            png_or_jpg = true;
            break;

        case chara:
            iostream   = SDL_IOFromFile("texture/c05_012_27x27.png", "r");
            png_or_jpg = false;
            break;
        case enamy1:
            iostream   = SDL_IOFromFile("texturec03_001_27x27.png", "r");
            png_or_jpg = false;
            break;
        case enamy2:
            iostream   = SDL_IOFromFile("texture/c03_005_27x27.png", "r");
            png_or_jpg = false;
            break;
        case enamy3:
            iostream   = SDL_IOFromFile("texture/c03_015_27x27.png", "r");
            png_or_jpg = false;
            break;
        case enamy4:
            iostream   = SDL_IOFromFile("texture/c08_002_27x27.png", "r");
            png_or_jpg = false;
            break;

        default:
            return RPG_Texture_Loader_Error();
    }

    if (iostream == NULL) {
        return RPG_Texture_Loader_Error();
    }

    if (png_or_jpg) {
        x_Render->surface = IMG_LoadJPG_IO(iostream);
    } else {
        x_Render->surface = IMG_LoadPNG_IO(iostream);
    }
    if (x_Render->surface == NULL) {
        return RPG_Texture_Loader_Error();
    }

    x_Render->texture = SDL_CreateTextureFromSurface(*renderer, x_Render->surface);
    if (x_Render->texture == NULL) {
        printf("here\r\n");
        return RPG_Texture_Loader_Error();
    }

    printf("surface->w->%d\r\n", x_Render->surface->w);
    printf("surface->h->%d\r\n", x_Render->surface->h);

    return RPG_OK;
}

RPG_State_t RPG_Map_Loader(bit_map_t* map_border_p, texture_map_t map)
{
    FILE* fp;
    char len[96];

    switch (map) {
        case MAP_1:
            fp = fopen("bit_map/MAP_1.txt", "r");
            break;

        case MAP_2:
            fp = fopen("bit_map/MAP_2.txt", "r");
            break;

        case MAP_3:
            fp = fopen("bit_map/MAP_3.txt", "r");
            break;

        default:
            printf("map value error");
            return RPG_Error;
    }

    if (fp == NULL) {
        printf("bit_map is cannot opened");
        return RPG_Error;
    }
    fgets(len, 98, fp);

    for (uint8_t i = 0; i < 57; i++) {
        if (fgets(len, 98, fp) == NULL) {
            printf("fp cannot read line->%d\r\n", i);
        }
        printf("%d -> ", i + 1);
        for (uint8_t j = 0; j < 96; j++) {
            map_border_p->bit_map[i][j] = len[j];
            printf("%c", map_border_p->bit_map[i][j]);
        }
        printf("\r\n");
    }
    fclose(fp);

    return RPG_OK;
}

RPG_State_t RPG_Texture_Loader_Qnit(RPG_Win_Render_Handler_t* x_Render)
{
    SDL_DestroyTexture(x_Render->texture);
    return RPG_OK;
}

RPG_State_t RPG_Texture_Loader_Error()
{
    printf("loader error");
    printf("\r\n");

    return RPG_Error;
}
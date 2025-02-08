#pragma once
#ifndef SPRITE_H
#define SPRITE_H

#include "include/SDL.h"
#include <string>

class Sprite
{
public:
    // int sprite_x, int sprite_y, int sprite_width, int sprite_height, std::string texture_asset_path
    Sprite(int sprite_x, int sprite_y, int sprite_width,
           int sprite_height, std::string texture_asset_path);
    ~Sprite();

    void Draw();
    void sprite_events(SDL_Event &event, float &deltaTime);
    void SpriteMovments(float& deltaTime);

private:
    //int sprite_x, sprite_y;
    //int sprite_width,sprite_height;
    float angle;
    SDL_Texture *sprite_texture;
    SDL_Rect sprite_rect;
    SDL_Surface *sprite_surface;
};

#endif
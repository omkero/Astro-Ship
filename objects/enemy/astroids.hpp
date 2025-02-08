#pragma once
#ifndef ASTROID_H
#define ASTROID_H

#include "include/SDL.h"
#include <string>
#include "objects/player2D/Player2D.hpp"
#include <vector>
#include "ui/Text.h"

struct Astroid
{
    SDL_Rect astroid_rect;
    SDL_Surface *astroid_surface = nullptr;
    SDL_Texture *astroid_texture = nullptr;
    std::string direction = "right";
    float angle;
};

class Astroids
{
public:
    // int sprite_x, int sprite_y, int sprite_width, int sprite_height, std::string texture_asset_path
    Astroids(int astroids_x, int astroids_y, int astroids_width,
             int astroids_height, std::string texture_asset_path);
    ~Astroids();

    void Draw(Player2D &player, Text& scoore);
    void AstroidsMovments(float &deltaTime, SDL_Event &event);
    void GenerateNewAstroid(int x, int y, std::string direction);

private:
    std::vector<Astroid> astroid_vector;
    float angle;
    int astroid_speed;
    std::string texture_path;
    int astroids_height;
    int astroids_width;
};

#endif
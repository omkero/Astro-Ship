#pragma once
#ifndef ASTROID_H
#define ASTROID_H

#include "include/SDL.h"
#include <string>
#include "objects/player2D/Player2D.hpp"
#include <vector>
#include "ui/Text.h"
#include <mutex>

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
             int astroids_height, std::string texture_asset_path, SDL_Renderer* renderer);
    ~Astroids();

    void Draw(Player2D &player, Text& scoore, float& deltaTime, SDL_Renderer* renderer);
    void AstroidsMovments(float &deltaTime, SDL_Event &event);
    void GenerateNewAstroid(int x, int y, std::string direction, SDL_Renderer* renderer);
    void ClearAstroids();
    
private:
    std::vector<Astroid> astroid_vector;

    std::mutex asteroids_mutex;  // Mutex to protect shared resources
    std::chrono::steady_clock::time_point last_creation_time;
    int asteroid_creation_interval_ms = 500; // 1000ms (1 second)

    float angle;
    int astroid_speed = 7;
    std::string texture_path;
    int astroids_height;
    int astroids_width;

    SDL_Surface *global_astroid_surface;
    SDL_Texture *global_astroid_texture;

    SDL_Window *window;
};

#endif
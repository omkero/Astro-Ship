#pragma once
#ifndef PLAYER2D_H
#define PLAYER2D_H

#include "include/SDL.h"
#include <string>
#include "maps/SpaceBackground.hpp"
#include <vector>
#include "core/renderer/Renderer.hpp"

struct Bullet
{
    // Constructor to initialize Bullet
    Bullet(SDL_Rect rect, float vx, float vy, SDL_Texture *bullet_texture, SDL_Surface *bullet_surface)
    {
        this->rect = rect;
        this->vx = vx;
        this->vy = vy;
        this->bullet_texture = bullet_texture;
        this->bullet_surface = bullet_surface;
    }

    SDL_Rect rect;               // Rectangle to store position and size
    float vx;                    // Bullet velocity in x direction
    float vy;                    // Bullet velocity in y direction
    SDL_Texture *bullet_texture; // Texture for rendering bullet
    SDL_Surface *bullet_surface; // Surface to load texture from
};

class Player2D : public SpaceBackground
{
public:
    // int sprite_x, int sprite_y, int sprite_width, int sprite_height, std::string texture_asset_path
    Player2D(int sprite_x, int sprite_y, int sprite_width,
             int sprite_height, std::string texture_asset_path);
    ~Player2D();
    std::vector<Bullet> bullets;
    void Draw();
    void player_events(SDL_Event &event, float &deltaTime, bool& isMainMenu);
    void PlayerMovments(float &deltaTime, SDL_Event &event);
    void cleanupBullets();

    SDL_Rect get_player_rect();
    void HitByAstroidHandler();
 
    int health_num = 100;

private:
    float angle;
    float bullet_angle;
    const float PI = 3.14159265f;
    int pos_x_clicked = 0;
    int pos_y_clicked = 0;

    int player_alpha = 255;
    int player_speed = 200;
    int bullet_height = 40;
    int bullet_width = 40;
    int bullet_speed = 25;
    int hit_health_value = 1;

    SDL_Texture *player_texture;
    SDL_Rect player_rect;
    SDL_Surface *player_surface;

    SDL_Texture *bt_texture = nullptr;
    SDL_Surface *bt_surface = nullptr;

    SDL_Rect healt_border;
    SDL_Rect health;
};

#endif
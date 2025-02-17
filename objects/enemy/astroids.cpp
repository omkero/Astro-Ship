#include "astroids.hpp"
#include "include/SDL_image.h"
#include <iostream>
#include "core/renderer/Renderer.hpp"
#include "objects/player2D/Player2D.hpp"
#include "core/physics/detections.hpp"
#include <algorithm>
#include "core/window/Window.hpp"
#include <random>
#include <thread>

Astroids::Astroids(int astroids_x, int astroids_y, int ast_width,
                   int ast_height, std::string texture_asset_path, SDL_Renderer *renderer)
{
    window = Window::get_window();
    if (!window)
    {
        std::cerr << "renderer is null" << std::endl;
    }

    int window_width;
    int window_height;

    SDL_GetWindowSize(window, &window_width, &window_height);

    this->texture_path = texture_asset_path;
    this->astroids_height = ast_height;
    this->astroids_width = ast_width;

    this->global_astroid_surface = IMG_Load(this->texture_path.c_str());
    this->global_astroid_texture = SDL_CreateTextureFromSurface(renderer, global_astroid_surface);

    astroid_break_sound = Mix_LoadMUS("assets/sounds/mario_block_break_.mp3");
    if (!astroid_break_sound)
    {
        std::cerr << "Failed to load MP3! Mix_Error: " << Mix_GetError() << std::endl;
    }

    last_creation_time = std::chrono::steady_clock::now();
};

Astroids::~Astroids()
{
    for (auto &astroid : astroid_vector)
    {
        if (astroid.astroid_surface)
        {
            SDL_FreeSurface(astroid.astroid_surface);
        }
        if (astroid.astroid_texture)
        {
            SDL_DestroyTexture(astroid.astroid_texture);
        }
    }
}

void Astroids::Draw(Player2D &player, Text &scoore, float &deltaTime, SDL_Renderer *renderer)
{

    SDL_Color whiteColor = {255, 255, 255, 255};

    // Handle asteroid creation periodically
    auto current_time = std::chrono::steady_clock::now();
    auto time_since_last_creation = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_creation_time).count();

    if (time_since_last_creation >= asteroid_creation_interval_ms)
    {
        int window_width;
        int window_height;

        SDL_GetWindowSize(window, &window_width, &window_height);
        LevelConfiguration(scoore, renderer);
        last_creation_time = current_time; // Reset the timer
    }

    for (auto &astroid : astroid_vector)
    {
        SDL_RenderCopyEx(renderer, astroid.astroid_texture, NULL, &astroid.astroid_rect, astroid.angle, nullptr, SDL_FLIP_NONE);
    }

    for (auto &asteroid_it : astroid_vector)
    {
        if (Detections::isColiding(player.get_player_rect(), asteroid_it.astroid_rect))
        {
            player.HitByAstroidHandler();
        }
        if (asteroid_it.direction == "right")
        {
            asteroid_it.angle += 3;
            asteroid_it.astroid_rect.x += astroid_speed;
            //   asteroid_it.astroid_rect.y += 1;
        }
        if (asteroid_it.direction == "left")
        {
            asteroid_it.angle -= 3;
            asteroid_it.astroid_rect.x -= astroid_speed;
            //     asteroid_it.astroid_rect.y -= 1;
        }
    }

    for (auto bullet_it = player.bullets.begin(); bullet_it != player.bullets.end();)
    {
        bool bullet_removed = false;

        for (auto asteroid_it = astroid_vector.begin(); asteroid_it != astroid_vector.end();)
        {
            bool erased = false;

            int window_width;
            int window_height;

            SDL_GetWindowSize(window, &window_width, &window_height);

            if (Detections::isColiding(bullet_it->rect, asteroid_it->astroid_rect))
            {

                // you can enable this sound if you want

                /*
                 Mix_VolumeMusic(150);
                 Mix_PlayMusic(astroid_break_sound, 1);
                */

                // Remove the asteroid safely
                asteroid_it = astroid_vector.erase(asteroid_it);

                // Remove the bullet safely
                bullet_it = player.bullets.erase(bullet_it);
                bullet_removed = true;

                scoore.IncTextNum(1);
                scoore.ReCreateText(renderer);
                break; // Exit asteroid loop as bullet is removed
            }

            // Check if asteroid is out of window bounds
            if (asteroid_it->astroid_rect.y > window_height || asteroid_it->astroid_rect.y + asteroid_it->astroid_rect.h < 0 || asteroid_it->astroid_rect.x > window_width || asteroid_it->astroid_rect.x + asteroid_it->astroid_rect.w < 0)
            {
                asteroid_it = astroid_vector.erase(asteroid_it); // 'erase' returns the next valid iterator
                erased = true;                                   // Mark the asteroid as erased
            }

            if (!erased)
            {
                ++asteroid_it; // Move to the next asteroid
            }
        }

        if (!bullet_removed)
        {
            ++bullet_it; // Move to the next bullet only if it wasn't erased
        }
    }
}

void Astroids::GenerateNewAstroid(int x, int y, std::string direction, SDL_Renderer *renderer)
{
    SDL_Rect payload_rect;
    payload_rect.x = x;
    payload_rect.y = y;
    payload_rect.h = astroids_height;
    payload_rect.w = astroids_width;

    Astroid payload;

    payload.astroid_rect = payload_rect;
    payload.astroid_surface = global_astroid_surface;
    payload.astroid_texture = global_astroid_texture;
    payload.angle = 0;
    payload.direction = direction;

    astroid_vector.push_back(payload);
}

void Astroids::ClearAstroids()
{
    this->astroid_vector.clear();
}

void Astroids::LevelConfiguration(Text &scoore, SDL_Renderer *renderer)
{
    int window_width;
    int window_height;

    SDL_GetWindowSize(window, &window_width, &window_height);
    if (scoore.GetTextNum() >= 50) {
        astroid_speed = 3;
    }

    if (scoore.GetTextNum() >= 100) {
        astroid_speed = 4;
    }

    if (scoore.GetTextNum() >= 150) {
        astroid_speed = 5;
    }

    if (scoore.GetTextNum() >= 200) {
        asteroid_creation_interval_ms = 450;
    }

    if (scoore.GetTextNum() >= 270) {
        asteroid_creation_interval_ms = 400;
    }

    if (scoore.GetTextNum() >= 370) {
        astroid_speed = 6;
    }

    if (scoore.GetTextNum() >= 410) {
        asteroid_creation_interval_ms = 350;
    }

    if (scoore.GetTextNum() >= 525) {
        asteroid_creation_interval_ms = 300;
        astroid_speed = 7;
    }

    if (scoore.GetTextNum() >= 595) {
        asteroid_creation_interval_ms = 280;

    }

    if (scoore.GetTextNum() >= 680) {
        asteroid_creation_interval_ms = 270;
    }

    if (scoore.GetTextNum() >= 780) {
        asteroid_creation_interval_ms = 270;
        astroid_speed = 8;
    }

    if (scoore.GetTextNum() >= 1100) {
        asteroid_creation_interval_ms = 250;
        astroid_speed = 9;
    }

    if (scoore.GetTextNum() >= 2005) {
        astroid_speed = 10;
    }

    // Create a new asteroid after the specified interval
    GenerateNewAstroid(window_width, rand() % 800, "left", renderer);
    GenerateNewAstroid(0 - astroids_width, rand() % 800, "right", renderer);
}

void Astroids::SetAstroidCreationInterval(int num) {
    this->asteroid_creation_interval_ms = num;
}

void Astroids::SetAstroidSpeed(int num) {
    this->astroid_speed = num;
}
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
                   int ast_height, std::string texture_asset_path,  SDL_Renderer* renderer)
{
    SDL_Window *window = Window::get_window();
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

    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist_x(0, window_width);
    std::uniform_int_distribution<int> dist_y(0, window_height);

    int random_height = dist_y(engine);

    GenerateNewAstroid(0, dist_y(engine) + astroids_height, "right", renderer);
    GenerateNewAstroid(0, dist_y(engine) + astroids_height, "right", renderer);
    GenerateNewAstroid(window_width - astroids_width, dist_y(engine) + astroids_height, "left", renderer);
    GenerateNewAstroid(window_width - astroids_width, dist_y(engine) + astroids_height, "left", renderer);

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

void Astroids::Draw(Player2D &player, Text &scoore, float& deltaTime, SDL_Renderer* renderer)
{

    SDL_Color whiteColor = {255, 255, 255, 255};

    // Handle asteroid creation periodically
    auto current_time = std::chrono::steady_clock::now();
    auto time_since_last_creation = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_creation_time).count();
        
    if (time_since_last_creation >= asteroid_creation_interval_ms) {
        // Create a new asteroid after the specified interval
        GenerateNewAstroid(rand() % 640, rand() % 480, "left", renderer);
        last_creation_time = current_time; // Reset the timer
    }
    

    for (auto &astroid : astroid_vector)
    {
        SDL_RenderCopyEx(renderer, astroid.astroid_texture, NULL, &astroid.astroid_rect, astroid.angle, nullptr, SDL_FLIP_NONE);
    }

    for (auto &asteroid_it : astroid_vector)
    {
        if (asteroid_it.direction == "right")
        {
            asteroid_it.angle += 3;
            asteroid_it.astroid_rect.x += 1;
            asteroid_it.astroid_rect.y += 1;
        }
        if (asteroid_it.direction == "left")
        {
            asteroid_it.angle -= 3;
            asteroid_it.astroid_rect.x -= 1;
            asteroid_it.astroid_rect.y -= 1;
        }
    }

    for (auto bullet_it = player.bullets.begin(); bullet_it != player.bullets.end();)
    {
        bool bullet_removed = false;

        for (auto asteroid_it = astroid_vector.begin(); asteroid_it != astroid_vector.end();)
        {

            if (Detections::isColiding(bullet_it->rect, asteroid_it->astroid_rect))
            {

                // Remove the asteroid safely
                asteroid_it = astroid_vector.erase(asteroid_it);

                // Remove the bullet safely
                bullet_it = player.bullets.erase(bullet_it);
                bullet_removed = true;

                scoore.IncTextNum();
                scoore.ReCreateText(renderer);
                break; // Exit asteroid loop as bullet is removed
            }
            else
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

void Astroids::GenerateNewAstroid(int x, int y, std::string direction, SDL_Renderer* renderer)
{
    SDL_Rect payload_rect;
    payload_rect.x = x;
    payload_rect.y = y;
    payload_rect.h = astroids_height;
    payload_rect.w = astroids_width;

    Astroid payload;

    payload.astroid_rect = payload_rect;
    payload.astroid_surface = IMG_Load(this->texture_path.c_str());
    payload.astroid_texture = SDL_CreateTextureFromSurface(renderer, payload.astroid_surface);
    payload.angle = 0;
    payload.direction = direction;

    astroid_vector.push_back(payload);

}

// A helper function to handle the actual logic in a separate thread
void Astroids::CreateAsteroidTask(int window_width, int window_height,std::string direction) {
    // Generate asteroid at a set interval (100px from the top in your example)

}

void Astroids::RenderEverySeconds(int seconds)
{
 // nothing
}
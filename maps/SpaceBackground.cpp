#include "SpaceBackground.hpp"
#include "include/SDL.h"
#include "core/renderer/Renderer.hpp"
#include <iostream>
#include "objects/Shapes/RectangleShape.hpp"
#include "core/window/Window.hpp"
#include <random>
#include <thread>
#include <chrono>

SpaceBackground::SpaceBackground()
{
}

void SpaceBackground::Background()
{
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "renderer is null" << std::endl;
    }

    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null" << std::endl;
    }
    int window_width;
    int window_height;

    int star_count = 500;
    SDL_GetWindowSize(window, &window_width, &window_height);

    // draw background here
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Initialize stars only if the vector is empty
    if (stars.empty())
    {
        std::random_device seeder;
        std::mt19937 engine(seeder());
        std::uniform_int_distribution<int> dist_x(0, window_width);
        std::uniform_int_distribution<int> dist_y(0, window_height);

        for (int i = 0; i < 100; ++i)
        {
            stars.push_back({dist_x(engine), dist_y(engine)});
        }
    }
}

void SpaceBackground::EnableStarAnimation()
{
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "renderer is null" << std::endl;
    }
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null" << std::endl;
        return;
    }

    RectangleShape star;
    SDL_Color color = {255, 255, 255, 255};

    int window_width;
    int window_height;

    SDL_GetWindowSize(window, &window_width, &window_height);

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist_x(0, window_width);
    std::uniform_int_distribution<int> dist_y(0, window_height);

    int starX_Random = dist_x(engine);
    int starY_Random = dist_y(engine);

    // Move and draw stars
    for (auto &pos : stars)
    {

        // Horizontal wrapping
        if (pos.x > window_width)
        {
            pos.x = 0;
        }
        else if (pos.x < 0)
        {
            pos.x = window_width;
        }

        // Vertical wrapping
        if (pos.y > window_height)
        {
            pos.y = 0;
        }
        else if (pos.y < 0)
        {
            pos.y = window_height;
        }

        if (state[SDL_SCANCODE_UP])
        {
            pos.y += 1;
        }
        if (state[SDL_SCANCODE_DOWN])
        {
            pos.y -= 1;
        }
        if (state[SDL_SCANCODE_RIGHT])
        {
            pos.x -= 1;
        }
        if (state[SDL_SCANCODE_LEFT])
        {
            pos.x += 1;
        }

        star.Draw(pos.x, pos.y, 1, 1, color);
    }

    // SDL_RenderPresent(renderer);
}

void SpaceBackground::set_seed_count(int amount)
{
    seed_count += amount;
}
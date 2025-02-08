#include "Sprite.h"
#include <iostream>
#include "core/renderer/Renderer.hpp"
#include "include/SDL_image.h"
#include <thread>
#include <chrono>
#include <cmath>

Sprite::Sprite(int sprite_x, int sprite_y, int sprite_width, int sprite_height, std::string texture_asset_path)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }

    // create surfrace
    sprite_surface = IMG_Load(texture_asset_path.c_str());
    if (!sprite_surface)
    {
        std::cerr << "[ERROR] sprite_surface cannot be created. or the assets path wrong from Sprite.cpp" << std::endl;
        // SDL_Quit();
    }

    // create texture
    sprite_texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);
    if (!sprite_texture)
    {
        std::cerr << "[ERROR] cannot sprite_texture cannot be created. from Sprite.cpp" << std::endl;
    }

    sprite_rect.x = sprite_x;
    sprite_rect.y = sprite_y;
    sprite_rect.h = sprite_height;
    sprite_rect.w = sprite_width;
}

Sprite::~Sprite()
{
    if (sprite_texture)
    {
        SDL_DestroyTexture(sprite_texture);
    }
    if (sprite_surface)
    {
        SDL_FreeSurface(sprite_surface);
    }
    if (&sprite_rect)
    {
        delete &sprite_rect;
    }
}

void Sprite::Draw()
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }

    if (SDL_RenderCopyEx(renderer, sprite_texture, NULL, &sprite_rect, angle, nullptr, SDL_FLIP_NONE) != 0)
    {
        std::cerr << "[ERROR] SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
    }
}

void Sprite::sprite_events(SDL_Event &event, float &deltaTime)
{

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // you have a task just make the texture follow you when moving
    if (event.button.x >= sprite_rect.x && event.button.x <= sprite_rect.x + sprite_rect.w &&
        event.button.y >= sprite_rect.y && event.button.y <= sprite_rect.y + sprite_rect.h)
    {
        if (SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                sprite_rect.x = mouseX - (sprite_rect.w / 2);
                sprite_rect.y = mouseY - (sprite_rect.h / 2);
            }
        }
    }

    // let the sprite follow your mouse cursor only when the mouse is moving
    if (event.type == SDL_MOUSEMOTION)
    {
        float speed = 1.5f;
        int mouseX;
        int mouseY;
        const float PI = 3.1416;

        SDL_GetMouseState(&mouseX, &mouseY);

        int delta_x = sprite_rect.x + 50 - mouseX;
        int delta_y = sprite_rect.y + 50 - mouseY;

        // make the angle point to mouse cursor and rotate 360 degree
        angle = ((atan2(delta_y, delta_x) * 180.0000) / PI) - 90;
    }
}

void Sprite::SpriteMovments(float &deltaTime)
{
    int speed = 200; // Speed in pixels per second
    // Smooth movement using SDL_GetKeyboardState
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        sprite_rect.y -= deltaTime * speed;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        sprite_rect.y += deltaTime * speed;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        sprite_rect.x += deltaTime * speed;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        sprite_rect.x -= deltaTime * speed;
    }
}
#include "Player2D.hpp"
#include <iostream>
#include "core/renderer/Renderer.hpp"
#include "include/SDL_image.h"
#include <thread>
#include <chrono>
#include "core/window/Window.hpp"
#include "objects/Shapes/RectangleShape.hpp"
#include <cmath>

Player2D::Player2D(int sprite_x, int sprite_y, int sprite_width, int sprite_height, std::string texture_asset_path)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }

    // create surface
    player_surface = IMG_Load(texture_asset_path.c_str());
    if (!player_surface)
    {
        std::cerr << "[ERROR] sprite_surface cannot be created. or the assets path wrong from Sprite.cpp" << std::endl;
        // SDL_Quit();
    }

    // create texture
    player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
    if (!player_texture)
    {
        std::cerr << "[ERROR] cannot sprite_texture cannot be created. from Sprite.cpp" << std::endl;
    }

    player_rect.x = sprite_x;
    player_rect.y = sprite_y;
    player_rect.h = sprite_height;
    player_rect.w = sprite_width;

    // Load the bullet texture only once
    bt_surface = IMG_Load("assets/textures/space/laserBullet.png");
    if (!bt_surface)
    {
        std::cerr << "[ERROR] Unable to load bullet surface: " << SDL_GetError() << std::endl;
    }

    bt_texture = SDL_CreateTextureFromSurface(renderer, bt_surface);
    if (!bt_texture)
    {
        std::cerr << "[ERROR] Unable to create bullet texture: " << SDL_GetError() << std::endl;
    }

    healt_border.x = 10;
    healt_border.y = 35;
    healt_border.h = 20;
    healt_border.w = health_num + 4;

    health.x = 12;
    health.y = 37;
    health.h = 15;
    health.w = health_num;
}

Player2D::~Player2D()
{
    if (player_texture)
    {
        SDL_DestroyTexture(player_texture);
    }
    if (player_surface)
    {
        SDL_FreeSurface(player_surface);
    }
    if (bt_texture)
    {
        SDL_DestroyTexture(bt_texture);
    }
    if (bt_surface)
    {
        SDL_FreeSurface(bt_surface);
    }
    // No need to delete player_rect, it's automatically cleaned up when the object is destroyed
}

void Player2D::Draw()
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }

    if (SDL_RenderCopyEx(renderer, player_texture, NULL, &player_rect, angle, nullptr, SDL_FLIP_NONE) != 0)
    {
        std::cerr << "[ERROR] SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
    }
    SDL_Color health_color = {255,255,255,255};

    SDL_SetRenderDrawColor(renderer,health_color.r, health_color.g, health_color.b, health_color.a);
    SDL_RenderFillRect(renderer, &healt_border);


    health.w = health_num;
    SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &health);
}

bool isUp = false;
bool isDown = false;
bool isRight = false;
bool isLeft = false;

void Player2D::player_events(SDL_Event &event, float &deltaTime,  bool& isMainMenu)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Window is null" << std::endl;
    }

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    int window_width;
    int window_height;

    SDL_GetWindowSize(window, &window_width, &window_height);



    // let the sprite follow your mouse cursor only when the mouse is moving
    if (event.type == SDL_MOUSEMOTION)
    {
        float speed = 1.5f;
        int mouseX;
        int mouseY;
        const float PI = 3.1416;

        SDL_GetMouseState(&mouseX, &mouseY);

        int delta_x = player_rect.x + 50 - mouseX;
        int delta_y = player_rect.y + 50 - mouseY;

        // make the angle point to mouse cursor and rotate 360 degree
        float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
        if (distance > 0.0f)
        {
            angle = ((atan2(delta_y, delta_x) * 180.0f) / PI) - 90;
        }
    }

    SDL_Color color = {255, 255, 255, 255};

    if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        // Get player's center (assuming the player's head is at the center-top)
        float player_center_x = player_rect.x + (player_rect.w / 2);
        float player_center_y = player_rect.y;  // Head position (top of the player)
    
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
    
        // Convert angle to radians
        float angle_rad = angle * (M_PI / 180.0);
    
        // Adjust bullet starting position based on player's rotation
        float bullet_x_pos = player_center_x + cos(angle_rad) * 20; // Offset from player
        float bullet_y_pos = player_center_y + sin(angle_rad) * 20; // Offset from player
    
        // Calculate direction to mouse
        float dx = mouseX - bullet_x_pos;
        float dy = mouseY - bullet_y_pos;
    
        // Normalize direction vector
        float distance = sqrt(dx * dx + dy * dy);
        if (distance == 0) return; // Avoid division by zero
    
        float vx = (dx / distance) * bullet_speed;
        float vy = (dy / distance) * bullet_speed;
    
        // Define the bullet's rectangle
        SDL_Rect bullet_rect = {static_cast<int>(bullet_x_pos), static_cast<int>(bullet_y_pos), bullet_width, bullet_height};
        Bullet bt(bullet_rect, vx, vy, bt_texture, bt_surface);
    
        // Add bullet to the vector
        bullets.push_back(bt);
    }
    
}

void Player2D::PlayerMovments(float &deltaTime, SDL_Event &event)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Window is null" << std::endl;
    }

    int window_width;
    int window_height;

    SDL_GetWindowSize(window, &window_width, &window_height);

    // Smooth movement using SDL_GetKeyboardState
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        player_rect.y -= deltaTime * player_speed;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        player_rect.y += deltaTime * player_speed;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        player_rect.x += deltaTime * player_speed;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        player_rect.x -= deltaTime * player_speed;
    }

    SDL_Color color = {255, 255, 255, 255};
    // Update and render bullets

    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (it->rect.x > window_width)
        {
            it = bullets.erase(it); // Remove and get the next valid iterator
        }
        else
        {
            if (it->bullet_surface && it->bullet_texture)
            {
                // Update bullet position
                it->rect.x += it->vx;
                it->rect.y += it->vy;
            }

            if (it->bullet_surface && it->bullet_texture)
            {
                // Render the bullet
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                if (SDL_RenderCopyEx(renderer, it->bullet_texture, NULL, &it->rect, 0, nullptr, SDL_FLIP_NONE) != 0)
                {
                    std::cerr << "[ERROR] SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
                }
            }

            ++it; // Move to the next bullet if no removal happened
        }
    }
}


SDL_Rect Player2D::get_player_rect() {
    return this->player_rect;
}

void Player2D::HitByAstroidHandler() {
    health_num -= hit_health_value;

    // just try to play opacity animation three times
    SDL_SetTextureAlphaMod(player_texture, 128); // 50% opacity
}
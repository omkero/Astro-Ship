#include "Text.h"
#include <string>
#include <iostream>
#include "core/renderer/Renderer.hpp"

Text::Text(SDL_Renderer *renderer, int fontSize)
{
    // load the font

    text_font = TTF_OpenFont("assets/fonts/RobotoMedium.ttf", fontSize);
    if (!text_font)
    {
        std::cerr << "Error cannot open or fin ttf file." << std::endl;
        throw std::runtime_error("Error cannot open or fin ttf file.");
        return;
    }
    SDL_Color white = {255, 255, 255};
    text_surface = TTF_RenderText_Blended(text_font, std::to_string(this->text_num).c_str(), white);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_surface" << std::endl;
        throw std::runtime_error("Error cannot init text_surface");
        return;
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_texture" << std::endl;
        throw std::runtime_error("Error cannot init text_texture");
        SDL_FreeSurface(text_surface);
        return;
    }
};

Text::~Text()
{
    if (text_surface)
    {
        SDL_FreeSurface(text_surface);
    }
    if (text_texture)
    {
        SDL_DestroyTexture(text_texture);
    }
    if (text_font)
    {
        TTF_CloseFont(text_font);
    }
}

void Text::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    text_rect.h = text_surface->h;
    text_rect.w = text_surface->w;

    // the default pos
    if (!text_rect.x)
        text_rect.x = 10;

    if (!text_rect.y)
        text_rect.y = 10;

    SDL_Color white = {255, 255, 255};
    // std::cout << text_num << std::endl;
    std::string nn = std::to_string(this->text_num);

    SDL_RenderCopy(renderer, text_texture, NULL, &text_rect);
}

void Text::SetTextPos(int x, int y)
{
    text_rect.x = x;
    text_rect.y = y;
}

void Text::IncTextNum()
{
    this->text_num += 1;
}
void Text::ResetTextNum()
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null, Error from Sprite.cpp" << std::endl;
    }
    
    this->text_num = 0;

    SDL_Color white = {255, 255, 255};
    text_surface = TTF_RenderText_Blended(text_font, std::to_string(this->text_num).c_str(), white);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_surface" << std::endl;
        throw std::runtime_error("Error cannot init text_surface");
        return;
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_texture" << std::endl;
        throw std::runtime_error("Error cannot init text_texture");
        SDL_FreeSurface(text_surface);
        return;
    }
}

void Text::ReCreateText(SDL_Renderer *renderer)
{

    text_rect.h = text_surface->h;
    text_rect.w = text_surface->w;

    // the default pos
    if (!text_rect.x)
        text_rect.x = 10;

    if (!text_rect.y)
        text_rect.y = 10;

    SDL_Color white = {255, 255, 255};
    // std::cout << text_num << std::endl;
    std::string nn = std::to_string(this->text_num);

    text_surface = TTF_RenderText_Blended(text_font, nn.c_str(), white);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_surface" << std::endl;
        throw std::runtime_error("Error cannot init text_surface");
        return;
    }

    text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_surface)
    {
        std::cerr << "Error cannot init text_texture" << std::endl;
        throw std::runtime_error("Error cannot init text_texture");
        SDL_FreeSurface(text_surface);
        return;
    }
}
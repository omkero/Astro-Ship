#include "RectangleShape.hpp"
#include "core/renderer/Renderer.hpp"
#include <iostream>

RectangleShape::RectangleShape() {};

void RectangleShape::Draw(int x, int y, int h, int w, SDL_Color color)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null at RectangleShape.cpp" << std::endl;
    }
    SDL_Rect stars = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, color.r, color.b, color.g, color.a);
    SDL_RenderFillRect(renderer, &stars);
}
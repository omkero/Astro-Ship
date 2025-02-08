#pragma once
#ifndef RECTANGLESHAPE_HPP
#define RECTANGLESHAPE_HPP

#include "include/SDL.h"

class RectangleShape
{
public:
    RectangleShape();
    void Draw(int x, int y, int h, int w, SDL_Color color);
    SDL_Rect rect_shape;

private:
};

#endif
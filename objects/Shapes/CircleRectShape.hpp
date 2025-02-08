#pragma once
#ifndef CIRCLE_SHAPE_HPP
#define CIRCLE_SHAPE_HPP

#include "include/SDL.h"

class CircleRectShape
{
public:
    CircleRectShape();
    void DrawCircle(int centerX, int centerY, int radius, SDL_Color color);
    void DrawOutlinedCircle(int centerX, int centerY, int radius, SDL_Color color);
    void DrawCircleRectShape(int x, int y, int w, int h, int radius, SDL_Color color);
    void DrawQuarterCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, int quadrant, SDL_Color color);
    SDL_Rect rect_shape;

private:
};

#endif
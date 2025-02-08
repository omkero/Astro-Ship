#pragma once
#ifndef DETECTIONS_H
#define DETECTIONS_H

#include "include/SDL.h"
#include <string>

class Detections
{
    public:
    static bool isColiding(SDL_Rect primary_rect, SDL_Rect target_rect);
};

#endif
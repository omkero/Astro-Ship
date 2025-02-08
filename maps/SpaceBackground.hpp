#pragma once
#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "include/SDL.h"
#include <vector>

class SpaceBackground {
    public:
    SpaceBackground();
    void Background();

    static int get_seed_count();
    void set_seed_count(int amount);
    void EnableStarAnimation();

    private:
    std::vector<SDL_Point> stars; // Store star positions
    SDL_Rect star_rect;
    int seed_count = 1; // 1 is default value so the space_background stars will only rendered on time
};

#endif
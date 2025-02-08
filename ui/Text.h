#pragma once
#ifndef TEXT_H
#define TEXT_H

#include "include/SDL.h"
#include "include/SDL_ttf.h"
#include <string>

class Text {
    public:
    Text(SDL_Renderer *renderer, int fontSize);
    ~Text();
    void Draw(SDL_Renderer *renderer);
    void ReCreateText(SDL_Renderer *renderer);
    void SetTextPos(int x, int y);
    void IncTextNum();
    
    private:
    SDL_Rect text_rect;
    int text_num = 20;
    SDL_Surface *text_surface;
    SDL_Texture *text_texture;
    TTF_Font *text_font;
};

#endif
#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "include/SDL.h"
#include "include/SDL_ttf.h"

class Display {
    public:
    Display();
    ~Display();
    void DrawMainMenu(SDL_Event &event, bool &isMainMenu);
    void MainMenuEventHandler(SDL_Event &event, bool &isMainMenu);

    private:

    TTF_Font *resumeFont;


    SDL_Rect buttonClose;
    SDL_Surface *resumeTextSurface;
    SDL_Texture *resumeTextTexture;
    int buttonCloseAlpha = 255;

    SDL_Rect buttonPause;
    SDL_Surface *closeTextSurface;
    SDL_Texture *closeTextTexture;
    int buttonPauseAlpha = 255;
};

#endif
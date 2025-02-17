#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "include/SDL.h"
#include "include/SDL_ttf.h"
#include "objects/player2D/Player2D.hpp"
#include "ui/Text.h"

class Display {
    public:
    Display();
    ~Display();
    void DrawMainMenu(SDL_Event &event, bool &isMainMenu);
    void DrawGameOverMenu(SDL_Event &event, bool &isGameOver);
    void MainMenuEventHandler(SDL_Event &event, bool &isMainMenu);
    void PlayAgainEventHandler(SDL_Event &event, bool &isGameOver, Player2D &player, Text &text); //, Astroids &astroids

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

    SDL_Rect buttonPlayAgain;
    SDL_Surface *playAgainTextSurface;
    SDL_Texture *playAgainTextTexture;
    int buttonPlayAgainAlpha = 255;
};

#endif
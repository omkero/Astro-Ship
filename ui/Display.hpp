#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include "include/SDL.h"
#include "include/SDL_ttf.h"
#include "objects/player2D/Player2D.hpp"
#include "ui/Text.h"
#include "objects/enemy/astroids.hpp"

class Display {
    public:
    Display();
    ~Display();
    void DrawMainMenu(SDL_Event &event, bool &isMainMenu);
    void DrawGameOverMenu(SDL_Event &event, bool &isGameOver);
    void MainMenuEventHandler(SDL_Event &event, bool &isMainMenu);
    void PlayAgainEventHandler(SDL_Event &event, bool &isGameOver, Player2D &player, Text &text, Astroids &astroids); //, Astroids &astroids

    private:
    int fontSize = 19;
    int gameOverSize = 23;

    TTF_Font *resumeFont;
    TTF_Font *gameOverFont;

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

    SDL_Rect gameOverRect;
    SDL_Surface *gameOverTextSurface;
    SDL_Texture *gameOverTextTexture;
};

#endif
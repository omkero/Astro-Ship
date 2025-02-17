#include "Display.hpp"
#include "core/window/Window.hpp"
#include "core/renderer/Renderer.hpp"
#include <iostream>
#include "Button.h"
#include "include/SDL_ttf.h"
#include <functional>
#include <cstdlib>
#include "objects/enemy/astroids.hpp"

void ReduceButtonOpacity(SDL_Rect &rect, SDL_Renderer *renderer, int &alpha);
void ResetButtonOpacity(SDL_Rect &rect, SDL_Renderer *renderer, int &alpha);

void HandleClick(SDL_Rect &rect, SDL_Event &event, int &alpha, std::function<void()> func)
{
    // we stuck here finish it please

    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null" << std::endl;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        // Check if the mouse is within the button's rectangle
        if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
            event.button.y >= rect.y && event.button.y <= rect.y + rect.h)
        {
            // do nothing
            ReduceButtonOpacity(rect, renderer, alpha);
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
            event.button.y >= rect.y && event.button.y <= rect.y + rect.h)
        {
            ResetButtonOpacity(rect, renderer, alpha);
            func();
        }
        else
        {
            ResetButtonOpacity(rect, renderer, alpha);
        }
    }
}

Display::Display()
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null" << std::endl;
    }
    
    SDL_Color textColor = {255, 255, 255};
    resumeFont = TTF_OpenFont("assets/fonts/RobotoMedium.ttf", fontSize);
    if (!resumeFont)
    {
        std::cerr << "Error: TTF_OpenFont failed: " << TTF_GetError() << std::endl;
        return;
    }
    gameOverFont = TTF_OpenFont("assets/fonts/RubikMonoOneRegular.ttf", gameOverSize);
    if (!gameOverFont)
    {
        std::cerr << "Error: TTF_OpenFont failed: " << TTF_GetError() << std::endl;
        return;
    }
    resumeTextSurface = TTF_RenderText_Blended(resumeFont, "Resume", textColor);
    if (!resumeTextSurface)
    {
        std::cerr << "TTF_RenderText_Blended failed: " << TTF_GetError() << std::endl;
        return;
    }
    resumeTextTexture = SDL_CreateTextureFromSurface(renderer, resumeTextSurface);
    if (!resumeTextTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(resumeTextSurface);
        return;
    }

    closeTextSurface = TTF_RenderText_Blended(resumeFont, "Exit", textColor);
    if (!closeTextSurface)
    {
        std::cerr << "TTF_RenderText_Blended failed: " << TTF_GetError() << std::endl;
        return;
    }
    closeTextTexture = SDL_CreateTextureFromSurface(renderer, closeTextSurface);
    if (!closeTextTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(closeTextSurface);
        return;
    }

    playAgainTextSurface = TTF_RenderText_Blended(resumeFont, "Play Again", textColor);
    if (!playAgainTextSurface)
    {
        std::cerr << "TTF_RenderText_Blended failed: " << TTF_GetError() << std::endl;
        return;
    }
    playAgainTextTexture = SDL_CreateTextureFromSurface(renderer, playAgainTextSurface);
    if (!playAgainTextTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(playAgainTextSurface);
        return;
    }

    gameOverTextSurface = TTF_RenderText_Blended(gameOverFont, "Game Is Over", textColor);
    if (!gameOverTextSurface)
    {
        std::cerr << "TTF_RenderText_Blended failed: " << TTF_GetError() << std::endl;
        return;
    }
    gameOverTextTexture = SDL_CreateTextureFromSurface(renderer, gameOverTextSurface);
    if (!playAgainTextTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(gameOverTextSurface);
        return;
    }
};

Display::~Display()
{
    if (resumeTextSurface)
    {
        SDL_FreeSurface(resumeTextSurface);
    }
    if (resumeTextTexture)
    {
        SDL_DestroyTexture(resumeTextTexture);
    }
    if (resumeFont)
    {
        TTF_CloseFont(resumeFont);
    }

    if (closeTextTexture)
    {
        SDL_DestroyTexture(closeTextTexture);
    }
    if (closeTextSurface)
    {
        SDL_FreeSurface(closeTextSurface);
    }
}

void Display::DrawMainMenu(SDL_Event &event, bool &isMainMenu)
{
    int window_width;
    int window_height;
    bool activeAnimation = false;
    int fontSize = 19;
    SDL_Color textColor = {255, 255, 255};

    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Error: Window is null" << std::endl;
    }
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null" << std::endl;
    }

    // draw background here
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable blending mode
    SDL_Rect main_menu;
    main_menu.h = window_height;
    main_menu.w = window_width;
    main_menu.x = 0;
    main_menu.y = 0;

    int pause_btn_height = 50;
    int pause_btn_width = 200;

    buttonPause.h = pause_btn_height;
    buttonPause.w = pause_btn_width;
    buttonPause.x = (window_width / 2) - (pause_btn_width / 2);
    buttonPause.y = (window_height / 2) - (pause_btn_height + pause_btn_height / 2);

    buttonClose.h = pause_btn_height;
    buttonClose.w = pause_btn_width;
    buttonClose.x = (window_width / 2) - (pause_btn_width / 2);
    buttonClose.y = (window_height / 2) + pause_btn_height / 2;

    // Create the rectangle for text positioning
    SDL_Rect textRect;
    textRect.h = resumeTextSurface->h;
    textRect.w = resumeTextSurface->w;
    textRect.x = buttonPause.x + (buttonPause.w / 2) - (textRect.w / 2); // Horizontal centering
    textRect.y = buttonPause.y + (buttonPause.h / 2) - (textRect.h / 2); // Vertical centering

    SDL_Rect textRect2;
    textRect2.h = closeTextSurface->h;
    textRect2.w = closeTextSurface->w;
    textRect2.x = buttonClose.x + (buttonClose.w / 2) - (textRect2.w / 2); // Horizontal centering
    textRect2.y = buttonClose.y + (buttonClose.h / 2) - (textRect2.h / 2); // Vertical centering

    SDL_SetRenderDrawColor(renderer, 46, 46, 46, 255); // RGBA (Alpha 180 for transparency)
    SDL_RenderFillRect(renderer, &main_menu);

    {
        SDL_SetRenderDrawColor(renderer, 94, 94, 94, buttonPauseAlpha); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &buttonPause);

        SDL_SetRenderDrawColor(renderer, 94, 94, 94, 0); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &textRect);

        SDL_RenderCopy(renderer, resumeTextTexture, NULL, &textRect);
    }

    {
        SDL_SetRenderDrawColor(renderer, 94, 94, 94, buttonCloseAlpha); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &buttonClose);

        SDL_SetRenderDrawColor(renderer, 94, 94, 94, 0); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &textRect2);

        SDL_RenderCopy(renderer, closeTextTexture, NULL, &textRect2);
    }
}

void Display::DrawGameOverMenu(SDL_Event &event, bool &isGameOver)
{
    int window_width;
    int window_height;
    bool activeAnimation = false;
    int fontSize = 19;
    SDL_Color textColor = {255, 255, 255};

    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Error: Window is null" << std::endl;
    }
    SDL_GetWindowSize(window, &window_width, &window_height);
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null" << std::endl;
    }

    // draw background here
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable blending mode
    SDL_Rect main_menu;
    main_menu.h = window_height;
    main_menu.w = window_width;
    main_menu.x = 0;
    main_menu.y = 0;

    int pause_btn_height = 50;
    int pause_btn_width = 200;

    buttonPlayAgain.h = pause_btn_height;
    buttonPlayAgain.w = pause_btn_width;
    buttonPlayAgain.x = (window_width / 2) - (pause_btn_width / 2);
    buttonPlayAgain.y = (window_height / 2) - (pause_btn_height + pause_btn_height / 2);

    buttonClose.h = pause_btn_height;
    buttonClose.w = pause_btn_width;
    buttonClose.x = (window_width / 2) - (pause_btn_width / 2);
    buttonClose.y = (window_height / 2) + pause_btn_height / 2;

    // Create the rectangle for text positioning
    SDL_Rect textRect;
    textRect.h = playAgainTextSurface->h;
    textRect.w = playAgainTextSurface->w;
    textRect.x = buttonPlayAgain.x + (buttonPlayAgain.w / 2) - (textRect.w / 2); // Horizontal centering
    textRect.y = buttonPlayAgain.y + (buttonPlayAgain.h / 2) - (textRect.h / 2); // Vertical centering

    SDL_Rect textRect2;
    textRect2.h = closeTextSurface->h;
    textRect2.w = closeTextSurface->w;
    textRect2.x = buttonClose.x + (buttonClose.w / 2) - (textRect2.w / 2); // Horizontal centering
    textRect2.y = buttonClose.y + (buttonClose.h / 2) - (textRect2.h / 2); // Vertical centering

    SDL_Rect gameOverText;
    gameOverText.h = gameOverTextSurface->h;
    gameOverText.w = gameOverTextSurface->w;
    gameOverText.x = (window_width / 2) - (gameOverTextSurface->w / 2); // Vertical centering; // Horizontal centering
    gameOverText.y = 150;

    SDL_SetRenderDrawColor(renderer, 46, 46, 46, 255); // RGBA (Alpha 180 for transparency)
    SDL_RenderFillRect(renderer, &main_menu);

    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // RGBA (Alpha 180 for transparency)
     //   SDL_RenderFillRect(renderer, &gameOverText);

        SDL_RenderCopy(renderer, gameOverTextTexture, NULL, &gameOverText);
    }

    {
        SDL_SetRenderDrawColor(renderer, 94, 94, 94, buttonPlayAgainAlpha); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &buttonPlayAgain);

        SDL_SetRenderDrawColor(renderer, 94, 94, 94, 0); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &textRect);

        SDL_RenderCopy(renderer, playAgainTextTexture, NULL, &textRect);
    }

    {
        SDL_SetRenderDrawColor(renderer, 94, 94, 94, buttonCloseAlpha); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &buttonClose);

        SDL_SetRenderDrawColor(renderer, 94, 94, 94, 0); // RGBA (Alpha 180 for transparency)
        SDL_RenderFillRect(renderer, &textRect2);

        SDL_RenderCopy(renderer, closeTextTexture, NULL, &textRect2);
    }
}

void Display::MainMenuEventHandler(SDL_Event &event, bool &isMainMenu)
{
    HandleClick(buttonPause, event, buttonPauseAlpha, [&]()
                { isMainMenu = false; });
    HandleClick(buttonClose, event, buttonCloseAlpha, [&]()
                { 
                    // quit the game
                    SDL_Quit();
                    exit(0); });
}
void Display::PlayAgainEventHandler(SDL_Event &event, bool &isGameOver, Player2D &player, Text &text, Astroids &astroids) // , Astroids &astroids
{
    HandleClick(buttonPlayAgain, event, this->buttonPlayAgainAlpha, [&]()
                { 
                    // play again handler
                    player.health_num = 100;
                    astroids.ClearAstroids();
                    text.ResetTextNum();
                    player.CenterPlayerPos();
                    isGameOver = false; });
    HandleClick(buttonClose, event, buttonCloseAlpha, [&]()
                { 
                    // quit the game
                    SDL_Quit();
                    exit(0); });
}

void ReduceButtonOpacity(SDL_Rect &rect, SDL_Renderer *renderer, int &alpha)
{
    alpha = 100;
}

void ResetButtonOpacity(SDL_Rect &rect, SDL_Renderer *renderer, int &alpha)
{
    alpha = 255;
}
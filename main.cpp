// #define SDL_MAIN_HANDLED // Avoid SDL from defining main() for you

#include <include/SDL.h>
#include <include/SDL_ttf.h>
#include <include/SDL_mixer.h>
#include <include/SDL_image.h>
#include <iostream>
#include <vector>
#include <functional>
#include "ui/Text.h"
#include "ui/Button.h"
#include "core/window/Window.hpp"
#include "core/renderer/Renderer.hpp"
#include <string>
#include "objects/Sprite.h"
#include "objects/player2D/Player2D.hpp"
#include "maps/SpaceBackground.hpp"
#include "objects/Shapes/CircleRectShape.hpp"
#include "objects/enemy/astroids.hpp"
#include "ui/Display.hpp"
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <Windows.h>
#endif

// int main(int argc, char *argv[]) for console

// int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init could not be initialized! SDL_Error " << std::endl;
        SDL_Quit();
        return -1;
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_Init(IMG_INIT_PNG))
    {
        std::cerr << "SDL_INIT_VIDEO could not be initialized! SDL_Error " << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initialize SDL_mixer with format and channels
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return -1;
    }

    const int win_width = 600;
    const int win_height = 400;

    int resize_win_width;
    int resize_win_height;

    SDL_Event event;

    bool isRunning = true;
    bool activeAnimation = false;

    // SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_POPUP_MENU | SDL_WINDOW_RESIZABLE);
    // Access the global SDL_Window*
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Window is null!" << std::endl;
        SDL_Quit();
        return -1;
    }

    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "Renderer is null" << std::endl;
        SDL_Quit();
        return -1;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    // get the window height and width on resize
    SDL_GetWindowSize(window, &resize_win_width, &resize_win_height);
    const int targetFPS = 60;                   // Target FPS
    const int frameDuration = 1000 / targetFPS; // Duration of one frame in milliseconds

    int frameTime;

    int btnHeight = 30;
    int btnWidth = 50;

    Display display;

    Text scoore(renderer, 14);
    scoore.SetTextPos(10, 10);

    std::string btn_text1 = "Pause";
    Button btn(btnWidth, btnHeight, resize_win_width - btnWidth - 15, 10, renderer, btn_text1); // Button size and position
    btn.SetColor(68, 65, 66, 255);

    Player2D player((resize_win_width / 2) - 35, (resize_win_height / 2) - 35, 70, 70, "assets/textures/space/gray_ship.png");

    SpaceBackground backgroundClass;

    SDL_Color color = {255, 255, 255, 255};
    Astroids astr(0, 0, 80, 80, "assets/textures/space/astroid_gray.png", renderer);

    SDL_Color whiteColor = {255, 255, 255, 255};

    bool quit = true;
    bool isMainMenu = false;
    bool isGameOver = false;
    bool blockEvents = false;

    float angle = 0.0f;
    Uint32 lastFrameTime = SDL_GetTicks();

    while (quit)
    {
        Uint32 frameStart = SDL_GetTicks();                       // Capture the start time of the frame
        float deltaTime = (frameStart - lastFrameTime) / 1000.0f; // Calculate deltaTime in seconds
        lastFrameTime = frameStart;                               // Update for the next frame

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                isMainMenu = !isMainMenu;
            }

            if (isGameOver) {
                display.PlayAgainEventHandler(event, isGameOver, player, scoore , astr);
                // Prevent further event processing if the main menu is active
                continue;
            }
            if (isMainMenu)
            {
                display.MainMenuEventHandler(event, isMainMenu);

                // Prevent further event processing if the main menu is active
                continue;
            }

            if (isMainMenu == false && isGameOver == false)
            {

                player.player_events(event, deltaTime, isMainMenu);
                btn.EventsHandler(event, renderer, activeAnimation);
            }
        }

        btn.onClick(event, [&]()
                    { isMainMenu = true; });

        if (isMainMenu)
        {
            display.DrawMainMenu(event, isMainMenu);
            SDL_RenderPresent(renderer);
        }
        else if (isGameOver)
        {
            display.DrawGameOverMenu(event, isMainMenu);
            SDL_RenderPresent(renderer);
        }
        else
        {
            backgroundClass.Background();
            backgroundClass.EnableStarAnimation();

            astr.Draw(player, scoore, deltaTime, renderer);

            player.Draw(isGameOver);
            player.PlayerMovments(deltaTime, event);

            scoore.Draw(renderer);
            btn.Draw(renderer);

            SDL_RenderPresent(renderer);
        }

        // Cap the frame rate to 60 FPS
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDuration > frameTime)
        {
            SDL_Delay(frameDuration - frameTime);
        }
    }

    Mix_CloseAudio();
    btn.ButtonCleanUp();
    SDL_Quit();
    return 0;
}
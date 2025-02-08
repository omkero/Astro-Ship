#include "Renderer.hpp"
#include "core/window/Window.hpp"
#include <iostream>

Renderer::Renderer()
{
    SDL_Window *window = Window::get_window();
    if (!window)
    {
        std::cerr << "Window is null!" << std::endl;
        SDL_Quit();
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cerr << "Error creating SDL_Renderer!" << std::endl;
        SDL_Quit();
    }
};

Renderer::~Renderer()
{
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
}

Renderer& Renderer::get_instance() {
    static Renderer instance; // Singleton instance
    return instance;
}

SDL_Renderer* Renderer::get_renderer() {
    return get_instance().renderer;
}
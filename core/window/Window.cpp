#include "Window.hpp"
#include <iostream>

Window::Window() {
    const int win_width = 900;
    const int win_height = 600;

    window_flags = (SDL_WindowFlags)(SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL /* | SDL_WINDOW_RESIZABLE */);
    window = SDL_CreateWindow("Astro Ship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, window_flags);

    if (!window) {
        std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
    }
}

Window::~Window() {
    if (window) {
        SDL_DestroyWindow(window);
    }
}

Window& Window::get_instance() {
    static Window instance; // Singleton instance
    return instance;
}

SDL_Window* Window::get_window() {
    return get_instance().window;
}

#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "include/SDL.h"

class Window {
public:
    // Access the singleton instance
    static Window& get_instance();

    // Access the SDL_Window globally
    static SDL_Window* get_window();

private:
    Window();                              // Constructor is private
    ~Window();                             // Destructor
    Window(const Window&) = delete;       // Prevent copy construction
    Window& operator=(const Window&) = delete; // Prevent assignment

    SDL_Window* window;
    SDL_WindowFlags window_flags;
};

#endif

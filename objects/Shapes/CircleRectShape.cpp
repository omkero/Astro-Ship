#include "CircleRectShape.hpp"
#include "core/renderer/Renderer.hpp"
#include <iostream>

CircleRectShape::CircleRectShape() {};

// Method to draw a circle
void CircleRectShape::DrawOutlinedCircle(int centerX, int centerY, int radius, SDL_Color color)
{
    SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer)
    {
        std::cerr << "renderer is null at CircleRectShape.cpp" << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Midpoint Circle Algorithm to draw the circle
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        // Draw points in all octants
        SDL_RenderDrawPoint(renderer, centerX + x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY + x);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY + y);
        SDL_RenderDrawPoint(renderer, centerX - x, centerY - y);
        SDL_RenderDrawPoint(renderer, centerX - y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + y, centerY - x);
        SDL_RenderDrawPoint(renderer, centerX + x, centerY - y);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void CircleRectShape::DrawCircle(int centerX, int centerY, int radius, SDL_Color color) {
  SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer) {
        std::cerr << "renderer is null at CircleRectShape.cpp" << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Midpoint Circle Algorithm to draw the circle
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        // Draw horizontal lines to fill the circle
        SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX + x, centerY + y);
        SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX + x, centerY - y);
        SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX + y, centerY + x);
        SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX + y, centerY - x);

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

// Function to plot pixels with alpha blending
void SetPixelAlpha(SDL_Renderer* renderer, int x, int y, SDL_Color color, float alpha) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, (Uint8)(alpha * 255));
    SDL_RenderDrawPoint(renderer, x, y);
}

void CircleRectShape::DrawCircleRectShape(int x, int y, int w, int h, int radius, SDL_Color color) {
     SDL_Renderer *renderer = Renderer::get_renderer();
    if (!renderer) {
        std::cerr << "renderer is null at CircleRectShape.cpp" << std::endl;
        return;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Draw the filled rectangle (excluding the rounded corners)
    SDL_Rect innerRect = {x + radius, y, w - 2 * radius, h};
    SDL_RenderFillRect(renderer, &innerRect);

    innerRect = {x, y + radius, w, h - 2 * radius};
    SDL_RenderFillRect(renderer, &innerRect);

    // Draw the four rounded corners (quarter circles)
    DrawQuarterCircle(renderer, x + radius, y + radius, radius, 0, color);       // Top-left
    DrawQuarterCircle(renderer, x + w - radius, y + radius, radius, 1, color);  // Top-right
    DrawQuarterCircle(renderer, x + radius, y + h - radius, radius, 2, color);  // Bottom-left
    DrawQuarterCircle(renderer, x + w - radius, y + h - radius, radius, 3, color); // Bottom-right
}

// Helper function to draw a quarter circle
void CircleRectShape::DrawQuarterCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius, int quadrant, SDL_Color color) {
       int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        // Draw horizontal lines to fill the quarter circle
        switch (quadrant) {
            case 0: // Top-left
                SDL_RenderDrawLine(renderer, centerX - x, centerY - y, centerX, centerY - y);
                SDL_RenderDrawLine(renderer, centerX - y, centerY - x, centerX, centerY - x);
                break;
            case 1: // Top-right
                SDL_RenderDrawLine(renderer, centerX, centerY - y, centerX + x, centerY - y);
                SDL_RenderDrawLine(renderer, centerX, centerY - x, centerX + y, centerY - x);
                break;
            case 2: // Bottom-left
                SDL_RenderDrawLine(renderer, centerX - x, centerY + y, centerX, centerY + y);
                SDL_RenderDrawLine(renderer, centerX - y, centerY + x, centerX, centerY + x);
                break;
            case 3: // Bottom-right
                SDL_RenderDrawLine(renderer, centerX, centerY + y, centerX + x, centerY + y);
                SDL_RenderDrawLine(renderer, centerX, centerY + x, centerX + y, centerY + x);
                break;
        }

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}
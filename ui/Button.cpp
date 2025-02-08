#include "Button.h"
#include <iostream>
#include "include/SDL_ttf.h"

Button::Button(int w, int h, int x, int y, SDL_Renderer *renderer, std::string &button_text)
    : width(w), height(h), x_axis(x), y_axis(y), surfaceMessage(nullptr), Message(nullptr), Sans(nullptr)
{
    rect = {x_axis, y_axis, width, height};

    int fontSize = 14;
    Sans = TTF_OpenFont("assets/fonts/RobotoMedium.ttf", fontSize);
    if (!Sans)
    {
        std::cerr << "Error: TTF_OpenFont failed: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color White = {255, 255, 255};
    surfaceMessage = TTF_RenderText_Blended(Sans, button_text.c_str(), White);
    if (!surfaceMessage)
    {
        std::cerr << "TTF_RenderText_Blended failed: " << TTF_GetError() << std::endl;
        return;
    }

    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    if (!Message)
    {
        std::cerr << "SDL_CreateTextureFromSurface failed: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surfaceMessage);
        return;
    }
}

Button::~Button()
{
    // Destructor for cleanup
    if (surfaceMessage)
        SDL_FreeSurface(surfaceMessage);
    if (Message)
        SDL_DestroyTexture(Message);
    if (Sans)
        TTF_CloseFont(Sans);
}

void Button::SetColor(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;

    this->oldA = a;
}

void Button::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, this->r, this->g, this->b, this->a);

    // Create the rectangle for text positioning
    SDL_Rect textRect;
    textRect.h = surfaceMessage->h;
    textRect.w = surfaceMessage->w;
    textRect.x = rect.x + (rect.w / 2) - (textRect.w / 2); // Horizontal centering
    textRect.y = rect.y + (rect.h / 2) - (textRect.h / 2); // Vertical centering

    // Draw the button
    SDL_RenderFillRect(renderer, &rect);

    // Render the text
    SDL_RenderCopy(renderer, Message, NULL, &textRect);
}

void Button::reduceOpacity(SDL_Renderer *renderer)
{
    // Reduce the opacity of the button when not clicked
    this->oldA = this->a;
    this->a = this->a / 2; // Lower opacity by 50%
    this->Draw(renderer);  // Redraw the button with reduced opacity
}

void Button::resetOpacity(SDL_Renderer *renderer)
{
    // Reset the opacity to the original when clicked
    this->a = this->oldA;
    // this->Draw(renderer); // Redraw the button with original opacity
}

void Button::ReDrawAnimation(SDL_Renderer *renderer, bool &activeAnimation)
{
    SDL_SetRenderDrawColor(renderer, 56, 56, 57, 255);
    SDL_RenderClear(renderer);

    this->Draw(renderer);
 
   // isReDraw = false; // Reset the flag
}

void Button::onClick(SDL_Event &event, std::function<void()> func)
{
    functionHandler = func;
}

void Button::EventsHandler(SDL_Event &event, SDL_Renderer *renderer, bool &activeAnimation)
{
    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        // Check if the mouse is within the button's rectangle
        if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
            event.button.y >= rect.y && event.button.y <= rect.y + rect.h)
        {
            activeAnimation = true;

            this->reduceOpacity(renderer); // Reset opacity on click
            this->Draw(renderer);
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
    {
        if (event.button.x >= rect.x && event.button.x <= rect.x + rect.w &&
            event.button.y >= rect.y && event.button.y <= rect.y + rect.h)
        {
            this->isClicked = true;
            // Reset opacity after mouse button up
            this->resetOpacity(renderer);
            functionHandler();
            activeAnimation = true;
        }
        else
        {
            this->resetOpacity(renderer);
            activeAnimation = true;
        }
    }
    if (SDL_WINDOWEVENT)
    {
        if (event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;

            std::cout << "Window resized to " << newWidth << "x" << newHeight << std::endl;

            int newRectX = newWidth - rect.w - 15;
            int newRectY = 10;
            SetNewPos(newRectX, newRectY);
            ReDrawAnimation(renderer, activeAnimation);
        }
    }
}

void Button::SetNewPos(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Button::ButtonCleanUp()
{
    this->~Button();
}
#ifndef BUTTON_H
#define BUTTON_H

#include <include/SDL.h>
#include <functional>
#include "include/SDL_ttf.h"
#include <string>

class Button
{
public:
    Button(int w, int h, int x, int y, SDL_Renderer *renderer, std::string &button_text);
    ~Button();

    void SetColor(int r, int g, int b, int a);
    void Draw(SDL_Renderer *renderer);
    void reduceOpacity(SDL_Renderer *renderer);
    void resetOpacity(SDL_Renderer *renderer);
    void ReDrawAnimation(SDL_Renderer *renderer, bool &activeAnimation);

    // events
    void onClick(SDL_Event &event, std::function<void()> func);
    void EventsHandler(SDL_Event &event, SDL_Renderer *renderer, bool &activeAnimation);
    void ButtonCleanUp();

    // setters

    void SetNewPos(int x, int y);

private:

    int width, height;
    int x_axis, y_axis;
    int r, g, b, a; // Color components
    int oldA;       // Previous opacity for resetting
    SDL_Rect rect;  // Rectangle for button bounds
    bool isClicked = false;
    std::function<void()> functionHandler;
    bool isReDraw = false;
    SDL_Surface *surfaceMessage;
    SDL_Texture *Message;
    TTF_Font *Sans; // Declare Sans as a pointer to a TTF_Font
};

#endif

# if you want to implement drag and drop you can use this

    // you have a task just make the texture follow you when moving

    int mouseX;
    int mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    if (event.button.x >= your_rect.x && event.button.x <= your_rect.x + your_rect.w &&
        event.button.y >= your_rect.y && event.button.y <= your_rect.y + your_rect.h)
    {
        if (SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            if (SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
            {
                your_rect.x = mouseX - (your_rect.w / 2);
                your_rect.y = mouseY - (your_rect.h / 2);
            }
        }
    }

# if you want to make your object follow your mouse use this and make sure to create an angle and also rendercopEx
# you can see this in stack overflow 
# https://stackoverflow.com/questions/21174767/how-do-you-rotate-a-sprite-based-on-mouse-position

    if (event.type == SDL_MOUSEMOTION)
    {
        float speed = 1.5f;
        int mouseX;
        int mouseY;
        const float PI = 3.1416;

        SDL_GetMouseState(&mouseX, &mouseY);

        int delta_x = your_rect.x + 50 - mouseX;
        int delta_y = your_rect.y + 50 - mouseY;

        // make the angle point to mouse cursor and rotate 360 degree
        angle = ((atan2(delta_y, delta_x) * 180.0000) / PI) - 90;
    }

# rectangle or sprite movments this code must use inside game loop and outside the event loop or it will not be smooth
# you can use SDL_GetKeyboardState or just pass the original from main event loop

    // Smooth movement using SDL_GetKeyboardState

    int speed = 200; // Speed in pixels per second

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_UP])
    {
        your_rect.y -= deltaTime * speed;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        your_rect.y += deltaTime * speed;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        your_rect.x += deltaTime * speed;
    }
    if (state[SDL_SCANCODE_LEFT])
    {
        your_rect.x -= deltaTime * speed;
    }

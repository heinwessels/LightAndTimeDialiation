#include "renderer.hpp"

Shape::Shape(SDL_Renderer &sdl_renderer_){
    sdl_renderer = &sdl_renderer_;
}
void Shape::draw(){
    throw;  // Not implemented
}
Rectangle::Rectangle(SDL_Renderer &sdl_renderer_, float x1_, float x2_, float y1_, float y2_)
    : Shape(sdl_renderer_), x1(x1_), x2(x2_), y1(y1_), y2(y2_)
{
}
void Rectangle::draw(){
    throw;  // Not implemented
}


bool Renderer::init_window(){
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        //Create window
        window = SDL_CreateWindow("Universe Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (sdl_renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                // Setup TTF
                TTF_Init();
                gfont = TTF_OpenFont(gfont_path, 18);
                if (gfont == NULL) {
                    fprintf(stderr, "error: font not found\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return success;
}
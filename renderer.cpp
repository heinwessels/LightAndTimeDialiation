#include "renderer.hpp"


void Renderer::add_sprite(Sprite sprite){
    sprites[num_of_sprites++] = sprite;
}

void Renderer::draw_sprites(){
    for (int i = 0; i < num_of_sprites; i++)
        printf("%f\n", sprites[i].pos.x);
}

void Renderer::draw_circle(SDL_Renderer * renderer, float x, float y, float radius){

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
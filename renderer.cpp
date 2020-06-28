#include "renderer.hpp"

void Renderer::Rectangle::draw(SDL_Renderer *renderer, int x, int y, float scaling){
    draw_filled_rectangle(renderer, x, y, width * scaling, height * scaling, colour);
}
void Renderer::Circle::draw(SDL_Renderer *renderer, int x, int y, float scaling){
    draw_filled_circle(renderer, x, y, radius * scaling, colour);
}

Renderer::~Renderer(){
    TTF_Quit();
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::clear_screen(){
    SDL_SetRenderDrawColor( sdl_renderer, 0, 0, 0, 0 );
    SDL_RenderClear(sdl_renderer);
}
void Renderer::show_screen(){
    SDL_RenderPresent( sdl_renderer );
}

void Renderer::draw_filled_rectangle(SDL_Renderer *renderer, float x, float y, float width, float height, Colour colour){
    SDL_Rect rect;
    rect.x = (int) (x - width / 2.0);
    rect.y = (int) (y - height / 2.0);
    rect.w = (int) width;
    rect.h = (int) height;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0 );
    SDL_RenderFillRect(renderer, &rect);
}

void Renderer::draw_filled_circle(SDL_Renderer *renderer, float x, float y, float radius, Colour colour){
    Renderer::draw_filled_rectangle(renderer, x, y, radius*2, radius*2, colour);
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
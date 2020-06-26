#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "vec3.hpp"


class Graphic{

};


class Renderer{

    private:

    int screen_width = 1000;
    int screen_height = 1000;

    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
    TTF_Font *gfont;
    const char * gfont_path = "fonts/PixelSplitter-Bold.ttf";

    public:

    static const int max_num_of_graphics = 100;
    Graphic graphics [max_num_of_graphics];
    int num_of_graphics = 0;


    bool init_window();

};


#endif
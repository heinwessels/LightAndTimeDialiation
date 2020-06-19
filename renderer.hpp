#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "vec3.hpp"

class Sprite{
    public:

    Vec3<float> pos;

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

    static const int max_num_of_sprites = 100;
    Sprite sprites [max_num_of_sprites];
    int num_of_sprites = 0;


    bool init_window();

    void add_sprite(Sprite sprite);

    void draw_sprites();

    void draw_circle(SDL_Renderer * renderer, float x, float y, float radius);

};


#endif
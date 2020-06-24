#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "vec3.hpp"

class Shape{
private:
    SDL_Renderer *sdl_renderer;
public:
    Shape(SDL_Renderer &sdl_renderer_);
    int rgba [4];
    virtual void draw();
};
class Rectangle : public Shape{
public:
    float x1, x2, y1, y2;
    void draw();
};
class Circle : public Shape{
public:
    void draw();
};

class Graphic{
public:
    Shape *shapes;
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
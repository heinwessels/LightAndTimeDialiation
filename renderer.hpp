#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "vec3.hpp"

class Renderer{
public:

    class Colour{
    public:
        int r, g, b, a;
        Colour():r(0),g(0),b(0),a(0){};
        Colour(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {};
    };

    class Graphic{
    public:
        Colour colour;
        virtual void draw(SDL_Renderer *renderer, int x, int y, float scaling){};
    };
    class Rectangle : public Graphic{
    public:
        float width, height;
        Rectangle(float w, float h) : width(w), height(h){};
        virtual void draw(SDL_Renderer *renderer, int x, int y, float scaling);
    };
    class Circle : public Graphic{
    public:
        float radius;
        Circle(float r) : radius (r){};
        virtual void draw(SDL_Renderer *renderer, int x, int y, float scaling);
    };

    ~Renderer();

    bool init_window();
    void clear_screen();
    void show_screen();
    SDL_Renderer *get_renderer(){return sdl_renderer;}

    static void draw_filled_rectangle(SDL_Renderer *renderer, float x, float y, float width, float height, Colour colour);
    static void draw_filled_circle(SDL_Renderer *renderer, float x, float y, float radius, Colour colour);


private:
    int screen_width = 1000;
    int screen_height = 1000;

    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
    TTF_Font *gfont;
    const char * gfont_path = "fonts/PixelSplitter-Bold.ttf";
};


#endif
#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>
#include <vector>
#include <string>

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
        virtual ~Graphic(){};
        Colour colour;
        virtual void draw(Renderer &renderer, int x, int y, float scaling){};
        virtual bool visible_on_screen(Renderer &renderer, int x, int y, float scaling) = 0;

    };
    class Rectangle : public Graphic{
    public:
        float width, height;
        Rectangle(float w, float h, Colour c) : width(w), height(h) {colour = c;};
        virtual void draw(Renderer &renderer, int x, int y, float scaling) override;
        bool visible_on_screen(Renderer &renderer, int x, int y, float scaling) override;
    };
    class Circle : public Graphic{
    public:
        float radius;
        Circle(float r, Colour c) : radius (r) {colour = c;};
        virtual void draw(Renderer &renderer, int x, int y, float scaling) override;
        bool visible_on_screen(Renderer &renderer, int x, int y, float scaling) override;
    };

    ~Renderer();

    bool init_window();
    void clear_screen();
    void show_screen();
    std::vector<SDL_Event> poll_events();
    void screenshot(std::string path);
    SDL_Renderer *get_renderer(){return sdl_renderer;}

    static void draw_filled_rectangle(Renderer &renderer, float x, float y, float width, float height, Colour colour);
    static void draw_filled_circle(Renderer &renderer, float x, float y, float radius, Colour colour);
    static void draw_line(Renderer &renderer, float x1, float y1, float x2, float y2, Colour colour);
    static void render_text(SDL_Renderer *renderer, int x, int y, const char *text, TTF_Font *font, SDL_Rect *rect, SDL_Color *color);


    int screen_width = 1000;
    int screen_height = 1000;

    SDL_Window *window;
    SDL_Renderer *sdl_renderer;
    TTF_Font *gfont;
    const char * gfont_path = "fonts/Thintel.ttf";
};


#endif
#include "renderer.hpp"

void Renderer::Rectangle::draw(Renderer &renderer, int x, int y, float scaling){
    if (visible_on_screen(renderer, x, y, scaling))
        draw_filled_rectangle(renderer, x, y, width * scaling, height * scaling, colour);
}
void Renderer::Circle::draw(Renderer &renderer, int x, int y, float scaling){
    if (visible_on_screen(renderer, x, y, scaling))
        draw_filled_circle(renderer, x, y, radius * scaling, colour);
}

bool Renderer::Rectangle::visible_on_screen(Renderer &renderer, int x, int y, float scaling){
    double graphic_width2 = width * scaling / 2.0;
    double graphic_height2 = height * scaling / 2.0;
    return  (x - graphic_width2 )     < (renderer.screen_width) &&
            (x + graphic_width2 )     > (0) &&
            (y - graphic_height2 )    < (renderer.screen_height) &&
            (y + graphic_height2 )    > (0);
}
bool Renderer::Circle::visible_on_screen(Renderer &renderer, int x, int y, float scaling){
    double scaled_radius = radius * scaling;
    double  dx = abs(x - renderer.screen_width / 2.0 ) - renderer.screen_width / 2,
            dy = abs(y - renderer.screen_height / 2.0) - renderer.screen_height / 2;
    if (dx > scaled_radius || dy > scaled_radius) { return false; }
    if (dx <= 0 || dy <= 0) { return true; }
    return (dx * dx + dy * dy <= scaled_radius * scaled_radius);
}

void Renderer::draw_filled_rectangle(Renderer &renderer, float x, float y, float width, float height, Colour colour){
    SDL_Rect rect;
    // The ceiling and minimum width/height of 1 is to ensure that at least a pixel is drawn.
    rect.x = (int) ceil(x - width / 2.0);
    rect.y = (int) ceil(y - height / 2.0);
    rect.w = (int) width > 1 ? width : 1;
    rect.h = (int) height > 1 ? height : 1;
    SDL_SetRenderDrawColor(renderer.sdl_renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRect(renderer.sdl_renderer, &rect);
}

void Renderer::draw_filled_circle(Renderer &renderer, float x, float y, float radius, Colour colour){
    // TODO: This is a inefficient algorithm. Try Bresenham.
    SDL_SetRenderDrawColor(renderer.sdl_renderer, colour.r, colour.g, colour.b, colour.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            if ((dx*dx + dy*dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer.sdl_renderer, x + dx, y + dy);
            }
        }
    }
}

void Renderer::draw_line(Renderer &renderer, float x1, float y1, float x2, float y2, Colour colour){
    SDL_SetRenderDrawColor(renderer.sdl_renderer, colour.r, colour.g, colour.b, colour.a);
    SDL_RenderDrawLine(renderer.sdl_renderer, x1, y1, x2, y2);
}

void Renderer::render_text(
    SDL_Renderer *renderer,
    int x, int y,
    const char *text,
    TTF_Font *font, SDL_Rect *rect, SDL_Color *color
) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}

std::vector<SDL_Event> Renderer::poll_events(){
    std::vector<SDL_Event> events;
    SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        events.push_back(event);
    }
    return events;
}

void Renderer::screenshot(std::string path){
    SDL_Surface *sshot = SDL_CreateRGBSurface(0, screen_width, screen_height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(sdl_renderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
    SDL_SaveBMP(sshot, ("screenshots/" + path).c_str());
    SDL_FreeSurface(sshot);
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
                gfont = TTF_OpenFont(gfont_path, 30);
                if (gfont == NULL) {
                    fprintf(stderr, "error: font not found\n");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    return success;
}
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "universe.hpp"
#include "renderer.hpp"
#include "matter.hpp"

class Controller{
public:
    void init();
    void run();
    void handle_input();

    Controller(){init();}
    ~Controller();
private:
    enum State {idle, running, single_step, exit};
    State state = running;
    Renderer *renderer;
    Universe *universe;
};

#endif
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <vector>
#include <ctime>
#include <chrono>

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

    Controller(){};
    ~Controller();
private:

    double simulation_speed = 10000.0;          // In simulated seconds per second
    static constexpr double time_step_max = 100.0;
    static constexpr double fps_limit = 30.0;

    enum State {idle, running, single_step, exit};
    State state = running;
    Renderer *renderer;
    Universe *universe;
};

#endif
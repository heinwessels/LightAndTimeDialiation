#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <memory>
#include <vector>
#include <ctime>
#include <chrono>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "universe.hpp"
#include "renderer.hpp"
#include "matter.hpp"
#include "universe_template.hpp"

class Controller{
public:
    void init();
    void run();

    Controller(){};
    ~Controller(){};
private:

    double simulation_speed = 60*60;          // In simulated seconds per second
    static constexpr double time_step_max = 100.0;
    static constexpr double fps_limit = 10.0;

    bool hide_ui = false;

    enum State {idle, running, single_step, exit};
    State state = running;

    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Universe> universe;

    void handle_input();
    void draw_information(double meas_sim_speed, double meas_single_step, double sim_time_step, double meas_fps, double sim_time_passed, double meas_render_time);
    std::string seconds_to_time_string(std::string pre, double seconds, std::string post);
};

#endif
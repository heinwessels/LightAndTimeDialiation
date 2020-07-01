#include "contoller.hpp"


void Controller::init(){

    // Setup Renderer
    renderer = new Renderer();
    renderer->init_window();

    // Create Universe
    universe = new Universe(*renderer);

    // Create Earth
    Matter * earth = new Matter(
        (double)(6e24),
        Vec3<double> (0, 0 , 0),
        Vec3<double> (0, 0, 0)
    );
    Physics::Circle earth_colbox (6378100, &earth->pos);
    earth->add_collisionbox(&earth_colbox);
    Renderer::Circle earth_graphic (earth_colbox.radius, Renderer::Colour(0, 0, 255, 0));
    earth->add_graphic(&earth_graphic);
    universe->add_matter(earth);

    // Create Moon
    Matter * moon = new Matter(
        (double)(7.35e22),
        Vec3<double> (384400000, 0, 0),
        Vec3<double> (0, 1022, 0)
    );
    Physics::Circle moon_colbox (1738100, &moon->pos);
    moon->add_collisionbox(&moon_colbox);
    Renderer::Circle moon_graphic (moon_colbox.radius, Renderer::Colour(255, 255, 255, 0));
    moon->add_graphic(&moon_graphic);
    universe->add_matter(moon);

    // Setup Observer
    universe->observer.ref_pos = new Vec3<double>(0);
    universe->observer.speed = new Vec3<double>(0);
    universe->observer.ref_scale = (double)renderer->screen_width / (moon->pos.x * 3);
}

Controller::~Controller(){
    delete universe;
    delete renderer;
}

void Controller::run(){
    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;

    sec time_to_simulate_single_step (0.000001);
    sec time_to_render (0);
    sec time_to_loop (1.0 / fps_limit);
    double sim_time_passed = 0; // In seconds
    const sec time_per_frame (1.0 / fps_limit);


    while (state != exit){

        auto time_loop_start = clock::now();

        // Handle Simulation
        // --------------------------------------------------
        int number_of_sim_steps = 0;
        sec time_left_to_sim = sec(1.0 / fps_limit) - time_to_render;
        double time_step = simulation_speed * time_to_simulate_single_step.count();
        time_step = time_step < time_step_max ? time_step : time_step_max;
        while(time_left_to_sim > time_to_simulate_single_step || !number_of_sim_steps){

            if (state == running || state == single_step){

                universe->step(time_step);
                sim_time_passed += time_step;

                if (state == single_step)
                    state = idle;
            }

            // Calculate the amount of time we can still use to simulate
            time_left_to_sim = (time_per_frame - time_to_render)
                                - (clock::now() - time_loop_start);

            number_of_sim_steps++;
        }
        // Average time it took to simualate a single step
        time_to_simulate_single_step = (clock::now() - time_loop_start) / number_of_sim_steps;

        // Handle Rendering
        // --------------------------------------------------
        const auto time_render_start = clock::now();
        universe->draw();
        handle_input();
        draw_information(
            number_of_sim_steps * time_step / time_to_loop.count(),
            time_step,
            1.0 / time_to_loop.count(),
            sim_time_passed,
            time_to_render.count()
        );

        time_to_loop = clock::now() - time_loop_start;
        time_to_render = clock::now() - time_render_start;
    }
}

void Controller::draw_information(
    double meas_sim_speed,
    double sim_time_step,
    double meas_fps,
    double sim_time_passed,
    double meas_render_time
){
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect rect;

    int y_spacing = 20;
    int x_2nd_col = 220;

    renderer->render_text(
        renderer->sdl_renderer, 10, 10,
        std::string("Set Sim Speed:").c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, 10,
        seconds_to_time_string(
            std::string(""), simulation_speed, std::string("   per second")
        ).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->render_text(
        renderer->sdl_renderer, 10, rect.y + y_spacing,
        std::string("Measured Sim Speed:").c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, rect.y,
        seconds_to_time_string(
            std::string(""), meas_sim_speed, std::string("   per second")
        ).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->render_text(
        renderer->sdl_renderer, 10, rect.y + y_spacing,
        std::string("Simulation Time Passed:").c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, rect.y,
        seconds_to_time_string(
            std::string(""), sim_time_passed, std::string("")
        ).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->render_text(
        renderer->sdl_renderer, 10, rect.y + y_spacing,
        std::string("Simulation Time Step:").c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, rect.y,
        seconds_to_time_string(
            std::string(""), sim_time_step, std::string("")
        ).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->render_text(
        renderer->sdl_renderer, 10, rect.y + y_spacing,
        (std::string("FPS (set to ")+std::to_string(int(fps_limit))+std::string("):")).c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, rect.y,
        std::to_string(meas_fps).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->render_text(
        renderer->sdl_renderer, 10, rect.y + y_spacing,
        std::string("Rendering Time:").c_str(),
        renderer->gfont, &rect, &color
    );
    renderer->render_text(
        renderer->sdl_renderer, x_2nd_col, rect.y,
        seconds_to_time_string(
            std::string(""), meas_render_time, std::string("")
        ).c_str(),
        renderer->gfont, &rect, &color
    );

    renderer->show_screen();
}

std::string Controller::seconds_to_time_string(std::string pre, double seconds, std::string post){

    const int max_length = 50;
    char text[max_length];

    double orig_seconds = seconds;
    int minutes = (int) seconds / 60;   seconds -= minutes * 60;
    int hours = (int) minutes / 60;     minutes -= hours * 60;
    int days = (int) hours / 24;        hours   -= days * 24;
    int years = (int) days / 365;       days    -= years * 365;
    if(orig_seconds < 1e-3){
        // Micro seconds
        snprintf(text, max_length,
        "%3.3f us",
        seconds * 1e6);
    }
    else if(orig_seconds < 1){
        // Milli seconds
        snprintf(text, max_length,
        "%3.3f ms",
        seconds * 1e3);
    }
    else if (orig_seconds < 60){
        // Seconds
        snprintf(text, max_length,
        "%3.3f s",
        seconds);
    }
    else if (orig_seconds < 60*60){
        // Minutes
        snprintf(text, max_length,
        "%02d m %02d s",
        minutes, int(seconds));
    }
    else if (orig_seconds < 60*60*24){
        // Hours
        snprintf(text, max_length,
        "%02d h %02d m %02d s",
        hours, minutes, int(seconds));
    }
    else if (orig_seconds < 60*60*24*365){
        // Days
        snprintf(text, max_length,
        "%03d d %02d h %02d m %02d s",
        days, hours, minutes, int(seconds));
    }
    else{
        // Years
        snprintf(text, max_length,
        "%d y %03d d %02d h %02d m %02d s",
        years, days, hours, minutes, int(seconds));
    }

    return pre + std::string(text) + post;
}

void Controller::handle_input(){
    std::vector<SDL_Event> events = renderer->poll_events();
    for (auto & event : events){

        if( event.type == SDL_QUIT )
        {
            state = exit;
        }

        if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_SPACE){
                if(state == idle)
                    state = running;
                else if(state == running)
                    state = idle;
            }
            if (event.key.keysym.sym == SDLK_s){
                state = single_step;
            }
            if(event.key.keysym.sym == SDLK_KP_PLUS){
                // Zoom in
                double step = pow(10,floor(log10(
                    universe->observer.zoom + pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                if (step > 0.1)
                    step = 0.1;
                universe->observer.zoom += step;
            }
            if(event.key.keysym.sym == SDLK_KP_MINUS){
                // Zoom out
                double step = pow(10,floor(log10(
                    universe->observer.zoom - pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                if (step > 0.1)
                    step = 0.1;
                universe->observer.zoom -= step;
            }
            if(event.key.keysym.sym == SDLK_PERIOD){
                // Speed up simulation
                simulation_speed += 60;
            }
            if(event.key.keysym.sym == SDLK_COMMA){
                // Slow down simulation
                simulation_speed -= 60;
            }
            if(event.key.keysym.sym == SDLK_LEFT){
                // Move camera left
                universe->observer.cam_pos.x ++;
            }
            if(event.key.keysym.sym == SDLK_RIGHT){
                // Move camera right
                universe->observer.cam_pos.x --;
            }
            if(event.key.keysym.sym == SDLK_UP){
                // Move camera up
                universe->observer.cam_pos.y ++;
            }
            if(event.key.keysym.sym == SDLK_DOWN){
                // Move camera down
                universe->observer.cam_pos.y --;
            }
        }
    }
}
#include "contoller.hpp"


void Controller::init(){

    // Setup Renderer
    renderer = std::make_unique<Renderer>();
    renderer->init_window();

    // Create Universe
    universe = std::make_unique<Universe>(*renderer);

    // Choose from templates
    // Template::sun_earth_moon(*universe);
    Template::three_body_figure_eight(*universe);
}

void Controller::run(){
    using clock = std::chrono::system_clock;
    using sec = std::chrono::duration<double>;

    sec time_to_simulate_single_step (0.1);  // Start slow
    sec time_to_render (0);
    sec time_to_loop (1.0 / fps_limit);
    double sim_time_passed = 0; // In seconds
    const sec time_per_frame (1.0 / fps_limit);


    while (state != exit){

        auto time_loop_start = clock::now();

        // Handle Simulation
        // --------------------------------------------------
        int number_of_sim_steps = 0;

        // Estimate how long we can sim for to keep up with FPS
        sec time_left_to_sim = sec(1.0 / fps_limit) - time_to_render;

        // Estimate required time step to keep up simulation speed
        double time_step = simulation_speed * time_to_simulate_single_step.count();
        if (time_step == 0){time_step = time_step_max;} // Will happen if running after idle.
        time_step = time_step < time_step_max ? time_step : time_step_max;
        if (state == single_step){time_step = time_step_max;}   // Otherwise single steps are too slow


        // Run the simulation, depending on fixed_step or not
        if (state == single_step || state == running){

            if(!fixed_step){
                while(time_left_to_sim > time_to_simulate_single_step || !number_of_sim_steps){

                    // Step the universe!
                    universe->step(time_step);
                    sim_time_passed += time_step;

                    // Calculate the amount of time we can still use to simulate
                    time_left_to_sim = (time_per_frame - time_to_render)
                                        - (clock::now() - time_loop_start);

                    number_of_sim_steps++;
                }
            }
            else if (state == running){
                // Fixed step (used for recording). A little different

                // Estimate how many steps we need based on the calculated time_step
                int required_num_of_steps = (int) ceil(simulation_speed / fps_limit / time_step);
                time_step = simulation_speed / fps_limit / required_num_of_steps; // Update time_step for rounded number of steps

                // Loop!
                while(number_of_sim_steps < required_num_of_steps){

                    // Step the universe!
                    universe->step(time_step);
                    sim_time_passed += time_step;

                    number_of_sim_steps++;
                }
            }
        }

        // Approximate average time it took to simualate a step (if any were made)
        if (number_of_sim_steps){
            time_to_simulate_single_step = (clock::now() - time_loop_start) / number_of_sim_steps;
        }
        else{
            time_to_simulate_single_step = sec(0);
        }

        // Handle Rendering
        // --------------------------------------------------
        const auto time_render_start = clock::now();
        renderer->clear_screen();
        universe->draw();
        handle_input();
        draw_information(
            number_of_sim_steps * time_step / time_to_loop.count(),
            time_to_simulate_single_step.count(),
            time_step,
            1.0 / time_to_loop.count(),
            sim_time_passed,
            time_to_render.count()
        );
        renderer->show_screen();
        if(record && state == running){
            renderer->screenshot("shot_" + std::to_string((int)sim_time_passed));
        }

        time_to_loop = clock::now() - time_loop_start;
        time_to_render = clock::now() - time_render_start;
    }
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
            if (event.key.keysym.sym == SDLK_h){
                hide_ui = !hide_ui;
            }
            if(event.key.keysym.sym == SDLK_KP_PLUS){
                // Zoom in
                double step = pow(10,floor(log10(
                    universe->observer.zoom + pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                universe->observer.zoom += step;
            }
            if(event.key.keysym.sym == SDLK_KP_MINUS){
                // Zoom out
                double step = pow(10,floor(log10(
                    universe->observer.zoom - pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                universe->observer.zoom -= step;
            }
            if(event.key.keysym.sym == SDLK_PERIOD){
                // Speed up simulation
                double step = pow(10,floor(log10(
                    simulation_speed + pow(10,floor(log10(simulation_speed)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                simulation_speed += step;
            }
            if(event.key.keysym.sym == SDLK_COMMA){
                // Slow down simulation
                double step = pow(10,floor(log10(
                    simulation_speed - pow(10,floor(log10(simulation_speed)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
                simulation_speed -= step;
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
            if(event.key.keysym.sym == SDLK_f){
                // Set fixed render/update step
                fixed_step = !fixed_step;
            }
            if(event.key.keysym.sym == SDLK_r){
                // Turn on/off recording
                record = !record;
            }
            if(event.key.keysym.sym == SDLK_n){
                // Track next object
                universe->camera_track_next_matter();
                universe->observer.cam_pos = Vec3<double> (0);
            }
            if(event.key.keysym.sym == SDLK_c){
                // Reset camera
                universe->observer.cam_pos.x = 0;
                universe->observer.cam_pos.y = 0;
                universe->observer.ref_pos = NULL;
            }
        }

        if (event.type == SDL_MOUSEBUTTONDOWN){
            // Nothing happensk
            Matter * m = universe->get_matter_at_pos(
                universe->observer.get_universe_pos_from_screen(Vec3<double> (event.motion.x, event.motion.y, 0))
            );
            if (m){
                universe->observer.ref_pos = &m->pos;
                universe->observer.cam_pos = Vec3<double> (0);
            }
        }
    }
}


void Controller::draw_information(
    double meas_sim_speed,
    double meas_single_step,
    double sim_time_step,
    double meas_fps,
    double sim_time_passed,
    double meas_render_time
){
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect rect;

    if (!hide_ui){
        int y_spacing = 20;
        int x_2nd_col = 220;

        // TOP LEFT
        /////////////////////////////////
        renderer->render_text(renderer->sdl_renderer, 10, 10, std::string("Set Sim Speed:").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, x_2nd_col, 10, seconds_to_time_string(
                std::string(""), simulation_speed, std::string("   per second")
            ).c_str(), renderer->gfont, &rect, &color
        );

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing, std::string("Measured Sim Speed:").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            seconds_to_time_string(
                std::string(""), meas_sim_speed, std::string("   per second")
            ).c_str(),
            renderer->gfont, &rect, &color
        );

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing, std::string("Simulation Time Passed:").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            seconds_to_time_string(
                std::string(""), sim_time_passed, std::string("")
            ).c_str(),
            renderer->gfont, &rect, &color
        );

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing, std::string("Simulation Time Step:").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            seconds_to_time_string(
                std::string(""), sim_time_step, std::string("")
            ).c_str(),
            renderer->gfont, &rect, &color
        );

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing,
            (std::string("FPS (set to ")+std::to_string(int(fps_limit))+std::string("):")).c_str(),
            renderer->gfont, &rect, &color
        );
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            std::to_string(meas_fps).c_str(),
            renderer->gfont, &rect, &color
        );

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing, std::string("Singe Step Time:").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            seconds_to_time_string(
                std::string(""), meas_single_step, std::string("")
            ).c_str(),
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

        renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing,
            std::string("Number of Objects:").c_str(), renderer->gfont, &rect, &color
        );
        renderer->render_text(
            renderer->sdl_renderer, x_2nd_col, rect.y,
            std::to_string(universe->get_num_of_matter()).c_str(),
            renderer->gfont, &rect, &color
        );

        rect.y += y_spacing;    // Give a little gap

        if (fixed_step){
            renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing,
                std::string("Fixed Step").c_str(), renderer->gfont, &rect, &color
            );
        }
        if (record){
            renderer->render_text(renderer->sdl_renderer, 10, rect.y + y_spacing,
                std::string("Recording...").c_str(), renderer->gfont, &rect, &color
            );
        }


        // BOTTOM LEFT
        int x_start = 10, y_start = renderer->screen_height - 90;
        int y_step = 20, x_step = 200;
        renderer->render_text(renderer->sdl_renderer, x_start, y_start, std::string("Hide UI: h").c_str(), renderer->gfont, &rect, &color);

        renderer->render_text(renderer->sdl_renderer, rect.x, rect.y + y_step,std::string("Run/Stop: space").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Singe Step: s").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Sim Speed: </>").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Fixed Step: f").c_str(), renderer->gfont, &rect, &color);

        renderer->render_text(renderer->sdl_renderer, x_start, rect.y + y_step,std::string("Camera: arrows").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Zoom: +/-").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Reset Camera: c").c_str(), renderer->gfont, &rect, &color);

        renderer->render_text(renderer->sdl_renderer, x_start, rect.y + y_step,std::string("Set Camera: click").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Next Body: n").c_str(), renderer->gfont, &rect, &color);
        renderer->render_text(renderer->sdl_renderer, rect.x + x_step, rect.y,std::string("Record: n").c_str(), renderer->gfont, &rect, &color);

    }
    else{
        renderer->render_text(
            renderer->sdl_renderer, 10, renderer->screen_height - 30,
            std::string("Show UI <h>").c_str(),
            renderer->gfont, &rect, &color
        );
    }
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
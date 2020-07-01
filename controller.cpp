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
    sec time_to_loop (0);
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
        // TODO draw some information text

        printf("-------------------------------------\n");
        printf("time_to_simulate_single_step:\t%.5f ms\n", time_to_simulate_single_step.count()*1000);
        printf("time_to_render:\t\t\t%.3f ms\n", time_to_render.count()*1000);
        printf("number_of_sim_steps:\t\t%d\n", number_of_sim_steps);
        printf("loop_time:\t\t\t%.3f ms\n", time_to_loop.count()*1000);
        printf("Simulation Speed:\t\t %.3f s/s\n", number_of_sim_steps * time_step / time_to_loop.count());

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
            if (event.key.keysym.sym == SDLK_PERIOD){
                state = single_step;
            }
            if(event.key.keysym.sym == SDLK_KP_PLUS){
                // Zoom in
                universe->observer.zoom += pow(10,floor(log10(
                    universe->observer.zoom + pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
            }
            if(event.key.keysym.sym == SDLK_KP_MINUS){
                // Zoom out
                universe->observer.zoom -= pow(10,floor(log10(
                    universe->observer.zoom - pow(10,floor(log10(universe->observer.zoom)) - 1)
                ))); // Calcuate step size depending on current value (eg. step = 0.1 if 0.3, and 0.01 if 0.06, etc.)
            }
            if(event.key.keysym.sym == SDLK_GREATER){
                // Speed up simulation
            }
            if(event.key.keysym.sym == SDLK_LESS){
                // Slow down simulation
            }
            if(event.key.keysym.sym == SDLK_GREATER){
                // Speed up simulation
            }
            if(event.key.keysym.sym == SDLK_LEFT){
                // Move camera left
                universe->observer.cam_pos.x ++;
            }
            if(event.key.keysym.sym == SDLK_RIGHT){
                // Move camera left
                universe->observer.cam_pos.x --;
            }
            if(event.key.keysym.sym == SDLK_UP){
                // Move camera left
                universe->observer.cam_pos.y ++;
            }
            if(event.key.keysym.sym == SDLK_DOWN){
                // Move camera left
                universe->observer.cam_pos.y --;
            }
        }
    }
}
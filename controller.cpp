#include "contoller.hpp"


void Controller::init(){

    // Setup Renderer
    renderer = new Renderer();
    renderer->init_window();

    // Create Universe
    universe = new Universe(*renderer);

    // Create Sun
    Matter * sun = new Matter(
        (double)(1.9884e30),
        Vec3<double> (0),
        Vec3<double> (0)
    );
    Physics::Circle sun_colbox (696342, &sun->pos);
    sun->add_collisionbox(&sun_colbox);
    Renderer::Circle sun_graphic (sun_colbox.radius, Renderer::Colour(255, 0, 0, 0));
    sun->add_graphic(&sun_graphic);
    universe->add_matter(sun);

    // Create Earth
    Matter * earth = new Matter(
        (double)(5.97237e24),
        Vec3<double> (149598023e3, 0 , 0),
        Vec3<double> (0, 2978e3, 0)
    );
    Physics::Circle earth_colbox (696342, &sun->pos);
    earth->add_collisionbox(&earth_colbox);
    Renderer::Circle earth_graphic (earth_colbox.radius, Renderer::Colour(0, 255, 0, 0));
    earth->add_graphic(&earth_graphic);
    universe->add_matter(earth);

    // Setup Observer
    universe->observer.pos = new Vec3<double>(0);
    universe->observer.speed = new Vec3<double>(0);
    universe->observer.scale = renderer->screen_width / (2.5 * earth->pos.x);
}

Controller::~Controller(){
    delete universe;
    delete renderer;
}

void Controller::run(){
    while (state != exit){

        handle_input();

        // universe->step(1);
        universe->draw();
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
                // Handle
            }
        }
    }
}
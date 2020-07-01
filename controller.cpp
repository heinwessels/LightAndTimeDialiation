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
    universe->observer.scale = (double)renderer->screen_width / (moon->pos.x * 3);
}

Controller::~Controller(){
    delete universe;
    delete renderer;
}

void Controller::run(){
    while (state != exit){

        handle_input();

        universe->step(100);
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
#include "contoller.hpp"


void Controller::init(){

    renderer = new Renderer();
    renderer->init_window();
    universe = new Universe(*renderer);

    Matter a (
        Vec3<double> (50, 50, 0),
        Vec3<double> (0),
        0
    );
    Renderer::Rectangle *gr_rect = new Renderer::Rectangle(20, 40); // This is a memory leak
    a.add_graphic(gr_rect);
    universe->add_matter(a);

    Matter b (
        Vec3<double> (300, 300, 0),
        Vec3<double> (0),
        0
    );
    Renderer::Circle *gr_circ = new Renderer::Circle(20);   // This is a memory leak
    b.add_graphic(
        gr_circ);
    universe->add_matter(b);
}

Controller::~Controller(){
    delete universe;
    delete renderer;
}

void Controller::run(){
    while (state != exit){

        handle_input();

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
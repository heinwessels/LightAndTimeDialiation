#include "contoller.hpp"


void Controller::init(){

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
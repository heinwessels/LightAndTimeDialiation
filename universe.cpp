#include "universe.hpp"


Universe::Universe(Renderer &r) : renderer(&r){};

void Universe::draw(){

    // First draw all matter
    for(int i = 0; i < num_of_matter; i++){
        // Draw

        // These should call functions inside the Matter::Shape
    }

    // Then draw some information on the screen
}
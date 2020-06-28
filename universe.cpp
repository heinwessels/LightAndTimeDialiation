#include "universe.hpp"


Universe::Universe(Renderer &r) : renderer(&r){};

void Universe::add_matter(Matter m){
    if (num_of_matter + 1 >= max_matter)
        throw;  // Array is full
    matter[num_of_matter++] = m;
}

void Universe::draw(){

    renderer->clear_screen();

    // First draw all matter
    for(int i = 0; i < num_of_matter; i++){

        // If graphic is empty (i.e. <Renderer::Graphic>), <draw()> will do nothing.
        matter[i].graphic->draw(
            renderer->get_renderer(),
            matter[i].pos.x,
            matter[i].pos.y,
            1
        );

    }

    // Then draw some information on the screen


    renderer->show_screen();
}
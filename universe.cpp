#include "universe.hpp"

void Universe::add_matter(Matter &m){
    if (num_of_matter + 1 >= max_matter)
        printf("WARNING: Matter overflow!\n");
    else
        matter[num_of_matter++] = &m;
}

void Universe::step(double time){

    // Calculate forces on all components

    handle_collisions();
}

void Universe::handle_collisions(){

    // Handle Collisions
    for (int i = 0; i < num_of_matter; i++){
        for (int j = i + 1; j < num_of_matter; j++){

            // First make sure there is matter at both indexes
            if (matter[i] && matter[j]){

                // Check for collision
                if (matter[i]->collision_box->collision_with(
                    matter[j]->collision_box
                )){

                    // Handle collision
                    if(matter[i]->collide_with_should_destroy(*matter[j])){
                        delete matter[i]; matter[i] =  NULL;
                    }
                    if(matter[j]->collide_with_should_destroy(*matter[i])){
                        delete matter[j]; matter[j] =  NULL;
                    }
                }
            }
        }
    }

    // Clean out NULLs out of array
    for (int i = 0; i < num_of_matter; i++){
        if(matter[i]){
            matter[i] = matter[num_of_matter];
            matter[num_of_matter--] = NULL;
        }
    }
}

void Universe::draw(){

    renderer->clear_screen();

    // First draw all matter
    for(int i = 0; i < num_of_matter; i++){

        // If graphic is empty (i.e. a <Renderer::Graphic> type), <draw()> will do nothing.
        matter[i]->graphic->draw(
            renderer->get_renderer(),
            matter[i]->pos.x,
            matter[i]->pos.y,
            1
        );

    }

    // Then draw some information on the screen


    renderer->show_screen();
}
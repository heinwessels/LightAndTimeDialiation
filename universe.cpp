#include "universe.hpp"

void Universe::add_matter(Matter *m){
    if (num_of_matter + 1 >= max_matter)
        printf("WARNING: Matter overflow!\n");
    else
        matter[num_of_matter++] = m;
}

void Universe::step(double time){

    handle_forces(time);
    handle_collisions();
}

void Universe::handle_forces(double time){

    Vec3<double> forces [max_matter];
    for (int i = 0; i < num_of_matter; i++){
        forces[i].x = 0; forces[i].y = 0;
    }

    for (int i = 0; i < num_of_matter; i++){
        for (int j = i + 1; j < num_of_matter; j++){

            // Calculate the force betwe en the two bodies
            Vec3<double> force = matter[i]->gravitational_force_to(*matter[j]);

            // Apply the force to the body if it's not stationary (both of them)
            if (matter[i]->affected_by_gravity)
                forces[i] += force;
            if (matter[j]->affected_by_gravity)
                forces[j] -= force;  // Inverting it for the other body
        }

        // When all the forces for this matter has been calculated, apply to the matter
        if(matter[i]->affected_by_gravity)
            matter[i]->apply_force_for_duration(
                forces[i],
                time
            );
    }
}



void Universe::handle_collisions(){

    // Handle Collisions
    for (int i = 0; i < num_of_matter; i++){
        for (int j = i + 1; j < num_of_matter; j++){

            // First make sure there is matter at both indexes
            if (matter[i]!=NULL && matter[j]!=NULL){

                // Check for collision
                if (matter[i]->collision_box->collision_with(
                    matter[j]->collision_box
                )){

                    // Handle collision
                    if(matter[i]->collide_with_should_destroy(matter[j])){
                        delete matter[i]; matter[i] =  NULL;
                    }
                    if(matter[j]->collide_with_should_destroy(matter[i])){
                        delete matter[j]; matter[j] =  NULL;
                    }
                }
            }
        }
    }

    // Clean out NULLs out of array
    for (int i = 0; i < num_of_matter; i++){
        if(matter[i] == NULL){
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
        Vec3<double> screen_pos = observer.get_screen_position(matter[i]->pos);
        matter[i]->graphic->draw(
            renderer->get_renderer(),
            screen_pos.x,
            screen_pos.y,
            observer.get_scale_factor()
        );
    }
}

Universe::~Universe(){
    delete observer.ref_pos;
    delete observer.speed;
}
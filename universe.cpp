#include "universe.hpp"

void Universe::add_matter(std::unique_ptr<Matter> m){
    // Passing <unique_ptr> by value to transfer ownership.
    // Use: Base add_matter(std::move(m));
    //      Base add_matter(std::make_unique<Matter>(new Matter(...));
    matter.push_back(std::move(m)); // Change the owenership from <m> to <matter>
}

void Universe::step(double time){

    handle_forces(time);
    handle_collisions();
}

void Universe::handle_forces(double time){

    for (int i = 0; i < matter.size(); i++){
        for (int j = i + 1; j < matter.size(); j++){

            // Is a Newtonian gravity calculation requried?
            if (matter[i]->affected_by_gravity || matter[i]->affected_by_gravity){

                // Calculate the force betwe en the two bodies
                Vec3<double> force = matter[i]->newtonian_gravitational_force_to(*matter[j]);

                // Apply the force to the body if it's not stationary (both of them)
                if (matter[i]->affected_by_gravity)
                    matter[i]->apply_force(force);
                if (matter[j]->affected_by_gravity)
                    matter[j]->apply_force(Vec3<double>(0.0)-force);
            }
        }

        // Step this piece of matter in time
        matter[i]->step(time);
    }
}

void Universe::handle_collisions(){

    // Handle Collisions
    int i = 0, j;
    while (i < matter.size() - 1){  // <i> must never reach last element, cause that will element <j>
        j = i + 1;
        while (j < matter.size()){

            // Check for collision
            if (matter[i]->check_collision_with(matter[j].get())){

                // Handle possible combining
                auto combined = matter[i]->combine_with(matter[j].get());
                if (combined != NULL){

                    // Combine the to matter by overwriting index <i>, and deleting index <j>
                    matter[i] = std::move(combined);
                    matter.erase (matter.begin() + j);
                }
                else{
                    // Some other possible things
                }
            }
            else{
                j ++;
            }
        }   // End of <j> loop

        i++;
    }   // End of <i> loop
}

void Universe::clear_matter_outside_boundary(
    Vec3<double> mininum,
    Vec3<double> maximum
){
    // Destroy matter outside certain boundary, if they allow it

    int i;
    while (i < matter.size()){
        if (matter[i]->clear_if_outside_boundary(mininum, maximum)){
            // Allowed to destroy, and outside boundary
            matter.erase (matter.begin() + i);
        }
        else{
            i++;
        }
    }
}

void Universe::draw(){

    // First draw all matter
    for(int i = 0; i < matter.size(); i++){

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
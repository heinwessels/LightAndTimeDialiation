#include "universe.hpp"

void Universe::add_matter(std::unique_ptr<Matter> m){
    // Passing <unique_ptr> by value to transfer ownership.
    // Use: Base add_matter(std::move(m));
    //      Base add_matter(std::make_unique<Matter>(new Matter(...));
    matter.push_back(std::move(m)); // Change the owenership from <m> to <matter>
}

void Universe::step(double time){

    handle_collisions();    // Do first, otherwise could have matter on top of each other giving insance forces
    handle_forces(time);
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
            if (matter[i]->check_collision_with(*matter[j])){

                // Handle possible combining
                auto combined = matter[i]->combine_with(matter[j].get());
                if (combined != NULL){

                    // OBSERVER: Check if we were following <i> or <j>, and update the camera if we were
                    if (observer.ref_pos == &matter[i]->pos || observer.ref_pos == &matter[j]->pos){
                        observer.ref_pos = &combined->pos;
                    }

                    // Combine the to matter by overwriting index <i>, and deleting index <j>
                    matter[i] = std::move(combined);
                    matter.erase (matter.begin() + j);
                }
                else{
                    // Some other possible things

                    j ++;
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
        matter[i]->draw(
            *renderer,
            observer.get_universe_offset(),
            observer.get_scale_factor()
        );
    }
}

void Universe::set_trail_length(int length){
    for (auto & m : matter){
        m->set_trail_length(length);
    }
}
void Universe::add_trail_to_matter(){
    for (auto & m : matter){
        m->add_pos_to_trail();
    }
}

Matter * Universe::get_matter_at_pos(Vec3<double> at){
    // Finds matter at this <pos>, based on graphic. (Used for GUI)
    for (auto & m : matter){
        if (m->is_at(at)){
            return m.get();         // Get is fine here, as it should not be called often
        }
    }
    return NULL;
}

void Universe::camera_track_next_matter(){
    // Link the observer to the next matter
    if (!observer.ref_pos){
        observer.ref_pos = &matter[0]->pos;
    }
    else{
        int i = 0;
        while (i < matter.size()){
            if (observer.ref_pos == &matter[i]->pos){
                observer.ref_pos = &matter[(i == matter.size() - 1) ? 0 : i + 1]->pos;

                i = matter.size();
            }
            i++;
        }
    }

}

Vec3<double> Universe::Observer::get_screen_position_from_universe(Vec3<double> uni_pos){
    Vec3<double> ref = ref_pos ? *ref_pos : Vec3<double> (0);
    return (uni_pos - ref) * (ref_scale * zoom) + screen_size / 2.0 + cam_pos*zoom;
}
Vec3<double> Universe::Observer::get_universe_pos_from_screen(Vec3<double> screen_pos){
    Vec3<double> ref = ref_pos ? *ref_pos : Vec3<double> (0);
    return (screen_pos - cam_pos * zoom - screen_size / 2.0) / (ref_scale * zoom) + ref;
}
Vec3<double> Universe::Observer::get_universe_offset(){
    // Get's the global universe offset in meter. This includes the centering on the screen.
    // If offsetting a universe location with this offset, and scaling that location,
    // it will result with the position on the screen
    Vec3<double> ref = ref_pos ? *ref_pos : Vec3<double> (0);
    return ref - (screen_size / 2.0 + cam_pos * zoom) / (ref_scale * zoom);
}
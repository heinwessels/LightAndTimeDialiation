#include "universe.hpp"

void Universe::add_matter(std::unique_ptr<Matter> m){
    // Passing <unique_ptr> by value to transfer ownership.
    // Use: Base add_matter(std::move(m));
    //      Base add_matter(std::unique_ptr<Matter>(new Matter(...));
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
            if (matter[i]->collision_with(matter[j].get())){

                // Need to do attempt destroy and destroy seperately, as it changes <matter>
                bool should_destroy_i = matter[i]->collide_with_should_destroy(matter[j].get());
                bool should_destroy_j = matter[j]->collide_with_should_destroy(matter[i].get());

                // Do destroying
                if(should_destroy_i){
                    matter.erase (matter.begin() + i);
                }
                if(should_destroy_j){
                    matter.erase (matter.begin() + j - (should_destroy_i ? 1 : 0)); // If <i> was destroyed, the <j>'s index will be one less
                }

                // What happens next depends on what was destroyed
                if (should_destroy_i){
                    j = i + 1;      // Remember, the next <i> element basically moved to the current index after erase
                }
                else if(should_destroy_j){
                    // Do nothing. <j> should stay the same, for the same reason why <i> remains the same for <erased_i>
                }
                else{
                    j++;
                }
            }
            else{
                j ++;
            }
        }   // End of <j> loop

        i++;
    }   // End of <i> loop
}

void Universe::clear_light_outside_boundary(
    Vec3<double> mininum,
    Vec3<double> maximum
){

}

void Universe::emit_light_from_point(
    Vec3<double> pos,
    double offset_radius,
    double amount
){
    for (double th = 0; th < 2*M_PI; th+=2*M_PI/amount){
        Vec3<double> dir (cos(th), sin(th), 0);
        add_matter(
            std::make_unique<Photon>(
                pos + dir * offset_radius,
                dir
            )
        );
    }
}

void Universe::draw(){

    renderer->clear_screen();

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
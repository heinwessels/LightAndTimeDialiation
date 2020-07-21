#include "matter.hpp"

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius, Renderer::Colour colour)
    : radius (radius), Matter(mass, pos, speed)
{
    collision_box = std::make_unique<Physics::Circle>(radius);
    graphic = std::make_unique<Renderer::Circle> (radius, colour);
}

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius)
    : Body(mass, pos, speed, radius, Renderer::Colour(0, 255, 0, 255)){}

bool Matter::check_collision_with(Matter const &other){
    return this->collision_box->collision_with(
        this->pos,
        other.pos,
        *other.collision_box
    );
}

std::unique_ptr<Matter> Body::combine_with(Matter * other){
    // This combining will only work with another body

    if (Body* other_body = dynamic_cast<Body*>(other)){
        // This is a valid collision with another Body.

        // Calculate the new location using the CoM of the two bodies
        auto new_pos = (this->pos * this->mass + other->pos * other->mass)
                        / (this->mass + other->mass);

        // Calculate speed using law of conservation of energy
        auto new_speed = (this->speed * this->mass + other->speed * other->mass)
                            / (this->mass + other->mass);

        // Calculate the new mass
        double new_mass = this->mass + other->mass;

        // Calculate new radius by averaging the two colliding bodies' radius,
        // and using the volume to calculate the density from mass
        double new_radius = pow(
            2 * new_mass / (
                this->mass / (this->radius*this->radius*this->radius) +
                other->mass / (other_body->radius*other_body->radius*other_body->radius)
            ),
            1.0/3.0
        );


        auto new_body = std::make_unique<Body>(
            new_mass, new_pos, new_speed, new_radius
        );

        // Copy the trail from the largest body (in mass)
        if(this->mass > other->mass){
            new_body->set_trail_length(this->trail.capacity()); // Update the trail length
            new_body->copy_trail_from(this->trail);
        }
        else{
            new_body->set_trail_length(other->trail.capacity()); // Update the trail length
            new_body->copy_trail_from(other->trail);
        }

        return std::move(new_body);
    }
    else{
        // Don't know how to handle this collision
        return NULL;
    }
}

double Body::get_density_based_on_mass_and_radius(double mass, double radius){
    return mass / (4.0 * M_PI / 3.0 * radius * radius * radius);
}
double Body::get_radius_based_on_mass_and_density(double mass, double density){
    return pow(mass / (4.0 * M_PI / 3.0 * density), 1.0/3.0);
}

void Matter::add_pos_to_trail(){
    trail.push_back(this->pos);
}

void Matter::copy_trail_from(boost::circular_buffer<Vec3<double>> other){
    for (auto & t : other){
        this->trail.push_back(t);
    }
}

void Matter::draw(Renderer &renderer, Vec3<double> offset, double scale){

    // First draw graphic
    Vec3<double> pos_to_draw = (this->pos - offset) * scale;
    this->graphic->draw(
        renderer,
        pos_to_draw.x,
        pos_to_draw.y,
        scale
    );

    // Now draw the trail behind the body
    for (int i = 0; i < (int)trail.size() - 1; i++){
        Vec3<double> pos1 = (trail[i] - offset) * scale;
        Vec3<double> pos2 = (trail[i + 1] - offset) * scale;

        renderer.draw_line(renderer, pos1.x, pos1.y, pos2.x, pos2.y, this->graphic->colour);
    }
}
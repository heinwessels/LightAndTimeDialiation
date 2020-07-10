#include "matter.hpp"

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius)
    : radius (radius), Matter(mass, pos, speed)
{
    collision_box = std::make_unique<Physics::Circle>(radius);
    graphic = std::make_unique<Renderer::Circle> (radius, Renderer::Colour(0, 255, 0, 255));
}

bool Matter::check_collision_with(Matter * other){
    return this->collision_box->collision_with(
        this->pos,
        other->pos,
        other->collision_box.get()
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

        // Calculate the new radius adding the area's of the two bodies
        double new_radius = sqrt(this->radius * this->radius + other_body->radius * other_body->radius);
        double new_mass = this->mass + other->mass;

        return std::make_unique<Body>(
            new_mass, new_pos, new_speed, new_radius
        );
    }
    else{
        // Don't know how to handle this collision
        return NULL;
    }
}
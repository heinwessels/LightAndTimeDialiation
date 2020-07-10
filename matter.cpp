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

        // Calculate the new radius adding through the adapted density from the combined mass
        double new_mass = this->mass + other->mass;
        double new_radius = get_radius_based_on_mass(new_mass);

        return std::make_unique<Body>(
            new_mass, new_pos, new_speed, new_radius
        );
    }
    else{
        // Don't know how to handle this collision
        return NULL;
    }
}

double Body::get_radius_based_on_mass(double mass){
    // This will questimate a nebula low density relative to stars' high density.
    // We will not use real values, but rather reverse calculate it in 3D

    const double top_radius = 695700000;    // [m]      Radius of the sun
    const double top_mass = 1.9884e30;      // [kg]     The mass of the sun
    const double bottom_radius = 1e5;       // [m]      Thumbsucking is the way of the engineer
    const double bottom_mass = 1e5;         // [kg]     This is a wild guess


    // Now interpolate between these two values
    return  (mass - top_mass)
                * (top_radius - bottom_radius) / (top_mass - bottom_mass)
                + bottom_radius;

}
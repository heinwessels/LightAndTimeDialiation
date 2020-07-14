#include "matter.hpp"

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius)
    : radius (radius), Matter(mass, pos, speed)
{
    collision_box = std::make_unique<Physics::Circle>(radius);
    graphic = std::make_unique<Renderer::Circle> (radius, Renderer::Colour(0, 255, 0, 255));
}

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
    // This will questimate a gas cloud's low density relative to a earth's high density.
    // We will not use real values, but rather reverse calculate it in 3D

    const double top_density = 5514;        // Average Density of earth [kg/m^3]
    const double top_mass = 6e24;           // The mass of the earth [kg]
    // Interesting, first used sun, but Earth is denser than the Sun.
    // I'm implementing bad physics.

    const double bottom_density = 3000.0;   // Some density of gas clouds
    const double bottom_mass = 1e15;        // When they weight this

    double density = (mass - bottom_mass)
                * (top_density - bottom_density) / (top_mass - bottom_mass)
                + bottom_density;

    // Override this for now. Using volume instead of area make a big difference in size.
    density = top_density;

    // Now get radius from density and mass for sphere
    return pow(
        mass / (4.0*M_PI/3.0 * density),
        1.0/3.0
    );
}
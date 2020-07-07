#include "matter.hpp"

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius)
    : Matter(mass, pos, speed)
{
    collision_box = std::make_unique<Physics::Circle>(radius);
    graphic = std::make_unique<Renderer::Circle> (radius, Renderer::Colour(0, 255, 0, 255));
}

Photon::Photon(Vec3<double> pos, Vec3<double> dir)
    : Matter(mass, pos, dir * Physics::c)
{
    affected_by_gravity = false;    // Not in the Newtonian way
    collision_box = std::make_unique<Physics::Rectangle>(0.1, 0.1); // Square to be quicker.
                    // And it's 0.1m big (!), but it can't be zero. Scale makes this negilable.
    graphic = std::make_unique<Renderer::Rectangle> (0, 0, Renderer::Colour(255, 255, 255, 255));   // Square to be quicker
}

bool Photon::clear_if_outside_boundary(Vec3<double> minimum, Vec3<double> maximum){
    // Photons can be cleared if outside a certain boundary
    return  (minimum.x > pos.x || pos.x > maximum.x) ||
            (minimum.y > pos.y || pos.y > maximum.y);
}

bool Matter::collision_with(Matter * other){
    return this->collision_box->collision_with(
        this->pos,
        other->pos,
        other->collision_box.get()
    );
}

bool Photon::collide_with_should_destroy(Matter *other){
    // Photons are destroyed if colliding with anything except other photons
    if (Photon* photon = dynamic_cast<Photon*>(other))
       return false;
    else
        return true;
}
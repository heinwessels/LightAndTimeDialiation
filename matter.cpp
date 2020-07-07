#include "matter.hpp"

void Matter::add_graphic(Renderer::Graphic *graphic){
    this->graphic = graphic->clone();
};

Matter::~Matter(){
    delete this->graphic;
}

Body::Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius)
    : Matter(mass, pos, speed)
{
    collision_box = std::make_unique<Physics::Circle>(radius);

    Renderer::Circle *g = new Renderer::Circle(radius, Renderer::Colour(0, 255, 0, 255));
    add_graphic(g);
    delete g;
}

Photon::Photon(Vec3<double> p, Vec3<double> dir)
{
    pos = p;
    mass = 0;
    affected_by_gravity = false;    // Not in the Newtonian way
    speed = dir * Physics::c;
    collision_box = std::make_unique<Physics::Circle>(0.1);

    Renderer::Circle *g = new Renderer::Circle(1.0, Renderer::Colour(255, 255, 255, 255));
    add_graphic(g);
    delete g;
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
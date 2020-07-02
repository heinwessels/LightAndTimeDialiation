#include "matter.hpp"


void Matter::add_collisionbox(Physics::CollisionBox *cb){
    collision_box = cb->clone();    // This needs to be deleted later
    collision_box->add_pos_ptr(&pos);
}

void Matter::add_graphic(Renderer::Graphic *graphic){
    this->graphic = graphic->clone();
};

Matter::~Matter(){
    delete this->collision_box;
    delete this->graphic;
}

Photon::Photon(Vec3<double> p, Vec3<double> dir){
    pos = p;
    mass = 0;
    affected_by_gravity = false;    // Not in the Newtonian way
    speed = dir * Physics::c;

    Physics::Circle *col = new Physics::Circle(0.1, &pos);
    add_collisionbox(col);
    delete col;
    Renderer::Circle *g = new Renderer::Circle(1.0, Renderer::Colour(255, 255, 255, 255));
    add_graphic(g);
    delete g;
}

bool Photon::collide_with_should_destroy(Matter *other){
    // Photon die if colliding with anything except other photons
    if (Photon* photon = dynamic_cast<Photon*>(other))
       return false;
    else
        return true;
}
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

bool Photon::collide_with_should_destroy(Matter *other){
    // Photon die if colliding with anything except other photons
    if (Photon* photon = dynamic_cast<Photon*>(other))
       return false;
    else
        return true;
}
#include "matter.hpp"


void Matter::add_collisionbox(Physics::CollisionBox *cb){
    collision_box = cb->clone();    // This needs to be deleted later
    collision_box->add_pos_ptr(&pos);
}

void Matter::add_graphic(Renderer::Graphic *graphic){
    this->graphic = graphic;
};

Matter::~Matter(){
    delete this->collision_box;
    this->collision_box = NULL;
}
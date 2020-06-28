#ifndef MATTER_HPP
#define MATTER_HPP

#include "vec3.hpp"
#include "renderer.hpp"
#include "physics.hpp"

class Matter{
public:

    Vec3<double> pos;
    Vec3<double> speed;
    double weight;
    Physics::CollisionBox *collision_box = NULL;
    Renderer::Graphic *graphic = NULL;

    bool ignore_forces = false;

    Matter(){};
    ~Matter();

    Matter(Vec3<double> p, Vec3<double> sp, double w) : pos(p), speed(sp), weight(w){};
    void add_collisionbox(Physics::CollisionBox *collision_box);
    void add_graphic(Renderer::Graphic *graphic);


};

#endif
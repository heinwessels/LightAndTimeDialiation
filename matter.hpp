#ifndef MATTER_HPP
#define MATTER_HPP

#include "vec3.hpp"
#include "renderer.hpp"
#include "physics.hpp"

class Matter : public Physics::Mass{
public:

    Physics::CollisionBox *collision_box = NULL;
    Renderer::Graphic *graphic = NULL;

    bool ignore_forces = false;

    Matter(){};
    ~Matter();

    Matter(double weight, Vec3<double> pos, Vec3<double> speed) : Physics::Mass(weight, pos, speed) {};
    void add_collisionbox(Physics::CollisionBox *collision_box);
    void add_graphic(Renderer::Graphic *graphic);
};

#endif
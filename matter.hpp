#ifndef MATTER_HPP
#define MATTER_HPP

#include <vector>

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

    virtual bool collide_with_should_destroy(Matter *other){return false;};
};

class Photon : public Matter{
public:
    Photon(Vec3<double> p, Vec3<double> dir);
    virtual bool collide_with_should_destroy(Matter *other);
};

#endif
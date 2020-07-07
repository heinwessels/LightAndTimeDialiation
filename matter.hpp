#ifndef MATTER_HPP
#define MATTER_HPP

#include <memory>
#include <vector>

#include "vec3.hpp"
#include "renderer.hpp"
#include "physics.hpp"

class Matter : public Physics::Mass{
public:

    std::unique_ptr<Physics::CollisionBox> collision_box;
    Renderer::Graphic *graphic = NULL;

    bool ignore_forces = false;

    Matter(){};
    Matter(double weight, Vec3<double> pos, Vec3<double> speed) : Physics::Mass(weight, pos, speed) {};
    ~Matter();

    void add_graphic(Renderer::Graphic *graphic);

    bool collision_with(Matter * other);
    virtual bool collide_with_should_destroy(Matter *other){return false;};
};

class Body : public Matter{
public:
    Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius);
    virtual bool collide_with_should_destroy(Matter *other){return false;};
};

class Photon : public Matter{
public:
    Photon(Vec3<double> p, Vec3<double> dir);
    virtual bool collide_with_should_destroy(Matter *other);
};

#endif
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
    virtual ~Matter(){delete this->graphic;}  // If a derived class object is deleted, this destructor is also called after the derived destructor.

    void add_graphic(Renderer::Graphic *graphic);

    bool collision_with(Matter * other);
    virtual bool collide_with_should_destroy(Matter *other){return false;};
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner) = 0;
};

class Body : public Matter{
public:
    Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius);
    virtual ~Body(){}
    virtual bool collide_with_should_destroy(Matter *other){return false;};
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner){return false;}
};

class Photon : public Matter{
public:
    Photon(Vec3<double> p, Vec3<double> dir);
    virtual ~Photon(){}
    virtual bool collide_with_should_destroy(Matter *other);
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner);
};

#endif
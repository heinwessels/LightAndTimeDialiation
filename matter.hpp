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
    std::unique_ptr<Renderer::Graphic> graphic;

    bool ignore_forces = false;

    Matter(){};
    Matter(double weight, Vec3<double> pos, Vec3<double> speed) : Physics::Mass(weight, pos, speed) {};
    virtual ~Matter(){}  // If a derived class object is deleted, this destructor is also called after the derived destructor.

    bool check_collision_with(Matter * other);
    virtual std::unique_ptr<Matter> combine_with(Matter * other) = 0;
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner) = 0;
};

class Body : public Matter{
public:
    double radius = 0;
    Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius);
    virtual ~Body(){}
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner){return false;}
    std::unique_ptr<Matter> combine_with(Matter * other);

    static double get_radius_based_on_mass(double mass);
};

#endif
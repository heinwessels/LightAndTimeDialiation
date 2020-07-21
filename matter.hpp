#ifndef MATTER_HPP
#define MATTER_HPP

#include <memory>
#include <vector>
#include <boost/circular_buffer.hpp>

#include "vec3.hpp"
#include "renderer.hpp"
#include "physics.hpp"

class Matter : public Physics::Mass{
public:

    std::unique_ptr<Physics::CollisionBox> collision_box;
    std::unique_ptr<Renderer::Graphic> graphic;

    bool ignore_forces = false;

    boost::circular_buffer<Vec3<double>> trail;

    Matter(double weight, Vec3<double> pos, Vec3<double> speed) : Physics::Mass(weight, pos, speed) {trail.set_capacity(0);};
    virtual ~Matter(){}  // If a derived class object is deleted, this destructor is also called after the derived destructor.

    bool check_collision_with(Matter const &other);
    virtual std::unique_ptr<Matter> combine_with(Matter * other) = 0;
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner) = 0;
    bool is_at(Vec3<double> at){return collision_box->is_at(pos, at);}

    void set_trail_length(int length){this->trail.set_capacity(length);}
    void copy_trail_from(boost::circular_buffer<Vec3<double>> other);
    void add_pos_to_trail();

    void draw(Renderer &renderer, Vec3<double> offset, double scale);

};

class Body : public Matter{
public:
    double radius = 0;
    Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius);
    Body(double mass, Vec3<double> pos, Vec3<double> speed, double radius, Renderer::Colour colour);
    virtual ~Body(){}
    virtual bool clear_if_outside_boundary(Vec3<double> lower_left_corner, Vec3<double> upper_right_corner){return false;}
    std::unique_ptr<Matter> combine_with(Matter * other);

    static double get_density_based_on_mass_and_radius(double mass, double radius);
    static double get_radius_based_on_mass_and_density(double mass, double density);
};

#endif
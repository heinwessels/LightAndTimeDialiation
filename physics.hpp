#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <math.h>

#include <stdio.h>
#include <stdexcept>

#include "vec3.hpp"

class Physics{
public:

    static constexpr double G = 6.6743015e-11;  // Gravitational Constant
    static constexpr double c = 299792458;      // Speed of Light

    class CollisionBox{
    public:
        virtual ~CollisionBox() {}
        virtual bool collision_with(Vec3<double> this_pos, Vec3<double> other_pos, CollisionBox *other_box) = 0;
        virtual CollisionBox *clone() const = 0;

    };
    class Rectangle: public CollisionBox{
    public:
        double width, height;
        Rectangle(double w, double h) : width(w), height(h) {};
        virtual bool collision_with(Vec3<double> this_pos, Vec3<double> other_pos, CollisionBox *other_box);
        virtual Rectangle *clone() const {return new Rectangle(*this);};
    };
    class Circle: public CollisionBox{
    public:
        double radius;
        Circle(double r) : radius (r) {};
        virtual bool collision_with(Vec3<double> this_pos, Vec3<double> other_pos, CollisionBox *other_box);
        virtual Circle *clone() const {return new Circle(*this);};
    };
    class CollisionHandler{
    public:
        static bool collision_between_rectangle_and_rectangle(Vec3<double> rect1_pos, Physics::Rectangle &rect1, Vec3<double> rect2_pos, Physics::Rectangle &rect2);
        static bool collision_between_rectangle_and_circle(Vec3<double> rect_pos, Physics::Rectangle &rect, Vec3<double> circ_pos, Physics::Circle &circ);
        static bool collision_between_circle_and_circle(Vec3<double> circ1_pos, Physics::Circle &circ1, Vec3<double> circ2_pos, Physics::Circle &circ2);
    };

    class Mass{
    public:
        double mass = 0;
        Vec3<double> pos = 0;
        Vec3<double> speed = 0;
        bool affected_by_gravity = true;
        Vec3<double> force_base = 0;        // Constant force applied on the mass (e.g. engine)
        Vec3<double> force_applied = 0;     // Force applied on this mass by universe
        Mass(){};
        Mass(double mass, Vec3<double> pos, Vec3<double> speed) : mass(mass), pos(pos), speed(speed) {};
        void apply_force(Vec3<double> force);
        void step(double time);
        Vec3<double> newtonian_gravitational_force_to(Physics::Mass &other);
    };
};

#endif
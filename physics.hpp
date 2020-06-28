#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <math.h>

#include <stdio.h>
#include <stdexcept>

#include "vec3.hpp"

class Physics{
public:
    class CollisionBox{
    public:
        virtual ~CollisionBox() {}
        Vec3<float>* pos = NULL;   // Pointer to the position vector of this collision box in space
        virtual bool collision_with(CollisionBox *box) = 0;
        void add_pos_ptr(Vec3<float> *p) {pos = p;}
        virtual CollisionBox *clone() const = 0;

    };
    class Rectangle: public CollisionBox{
    public:
        float width, height;
        Rectangle(float w, float h) : width(w), height(h) {};
        virtual bool collision_with(CollisionBox *box);
        virtual Rectangle *clone() const {return new Rectangle(*this);};
    };
    class Circle: public CollisionBox{
    public:
        float radius;
        Circle(float r) : radius (r) {};
        virtual bool collision_with(CollisionBox *box);
        virtual Circle *clone() const {return new Circle(*this);};
    };
    class CollisionHandler{
    public:
        static bool collision_between_rectangle_and_rectangle(Physics::Rectangle &rectangle1, Physics::Rectangle &rectangle2);
        static bool collision_between_rectangle_and_circle(Physics::Rectangle &rectangle, Physics::Circle &circle);
        static bool collision_between_circle_and_circle(Physics::Circle &circle1, Physics::Circle &circle2);
    };

};

#endif
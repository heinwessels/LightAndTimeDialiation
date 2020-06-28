#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <stdio.h>

#include "vec3.hpp"

class Physics{
public:
    class CollisionBox{
    public:
        Vec3<float>* pos;   // Pointer to the position vector of this collision box in space
        virtual bool collision_with(CollisionBox *box) = 0;
    protected:
        CollisionBox(){};
    };
    class Rectangle: public CollisionBox{
    public:
        float width, height;
        Rectangle(Vec3<float> *p, float w, float h) : width(w), height(h) {pos = p;};
        virtual bool collision_with(CollisionBox *box);
    };
    class Circle: public CollisionBox{
    public:
        float radius;
        Circle(Vec3<float> *p, float r) : radius (r) {pos = p;};
        virtual bool collision_with(CollisionBox *box);
    };
    class CollisionHandler{
    public:
        static bool collision_between_rectangle_and_rectangle(const Physics::Rectangle &rectangle1, const Physics::Rectangle &rectangle2);
        static bool collision_between_rectangle_and_circle(const Physics::Rectangle &rectangle, const Physics::Circle &circle);
        static bool collision_between_circle_and_circle(const Physics::Circle &circle1, const Physics::Circle &circle2);
    };

};

#endif
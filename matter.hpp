#ifndef MATTER_HPP
#define MATTER_HPP

#include "vec3.hpp"
#include "renderer.hpp"
// #include "universe.hpp"

class Matter{

public:

    class Shape{
    };
    // TODO Derived classes should not know about each other
    class Circle;
    class Rectangle: public Shape{
    public:
        float width, height;
        Rectangle(float w, float h) : width(w), height(h){};
        virtual bool collision_with(const Rectangle &rectangle);
        virtual bool collision_with(const Circle &circle);
    };
    class Circle: public Shape{
    public:
        float radius;
        Circle(float r) : radius (r){};
        virtual bool collision_with(const Rectangle &rectangle);
        virtual bool collision_with(const Circle &circle);
    };
    class ShapeCollisions{
    public:
        static bool collision_between_rectangle_and_rectangle(const Rectangle &rectangle1, const Rectangle &rectangle2);
        static bool collision_between_rectangle_and_circle(const Rectangle &rectangle, const Circle &circle);
        static bool collision_between_circle_and_circle(const Circle &circle1, const Circle &circle2);
    };


    Vec3<float> pos;
    Vec3<float> speed;
    float weight;
    Shape shape;
    bool ignore_forces = false;

    Renderer::Graphic *graphic;

    Matter(){};
    ~Matter(){};

    Matter(Vec3<float> p, Vec3<float> sp, float w, Shape sh) : pos(p), speed(sp), weight(w), shape(sh) {};
    void add_graphic(Renderer::Graphic *graphic){this->graphic = graphic;};

    // void step(Universe &universe);
};

#endif
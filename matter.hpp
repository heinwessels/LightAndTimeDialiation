#ifndef MATTER_HPP
#define MATTER_HPP

#include "vec3.hpp"
#include "renderer.hpp"
// #include "universe.hpp"

class Matter{

    private:
    Graphic graphic;

    public:

    class Rectangle;
    class Circle;
    class Shape{
    public:
        bool collision_between_rectangle_and_rectangle(const Rectangle &rectangle1, const Rectangle &rectangle2);
        bool collision_between_rectangle_and_circle(const Rectangle &rectangle, const Circle &circle);
        bool collision_between_circle_and_circle(const Circle &circle1, const Circle &circle2);
    };
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


    Vec3<float> pos;
    Vec3<float> speed;
    float weight;
    bool ignore_forces = false;

    Matter(){};
    ~Matter(){};

    Matter(Vec3<float> pos, Vec3<float> speed, float weight);

    void add_graphic(Graphic graphic);

    // void step(Universe &universe);
};

#endif
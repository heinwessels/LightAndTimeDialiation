#include <stdio.h>
#include <iostream>

#include "contoller.hpp"
#include "physics.hpp"

int main( int argc, char* args[] )
{
    Vec3<float> a (0, 0, 0);
    Vec3<float> b (20, 0, 0);

    Physics::Rectangle rectangle (&a, 20, 40);
    Physics::Circle circle (&b, 20);

    rectangle.collision_with(&rectangle);
    rectangle.collision_with(&circle);
    // circle.collision_with(rectangle);
    // circle.collision_with(circle);


    // Controller controller;
    // controller.run();
}
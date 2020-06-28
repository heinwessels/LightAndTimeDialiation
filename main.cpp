#include <stdio.h>
#include <iostream>

#include "contoller.hpp"
#include "physics.hpp"

int main( int argc, char* args[] )
{
    Vec3<double> a (0, 0, 0);
    Vec3<double> b (0, -21, 0);

    Physics::Rectangle rectangle1 (20, 20);
    rectangle1.add_pos_ptr(&a);
    // Physics::Rectangle rectangle2 (50, 20);
    // rectangle2.add_pos_ptr(&b);
    // Physics::Circle circle1 (20);
    // circle1.add_pos_ptr(&a);
    Physics::Circle circle2 (10);
    circle2.add_pos_ptr(&b);

    // printf("r1 vs r2: %d\n", rectangle1.collision_with(&rectangle2));
    // printf("c1 vs c2: %d\n", circle1.collision_with(&circle2));
    printf("r vs c: %d\n", rectangle1.collision_with(&circle2));


    // Controller controller;
    // controller.run();
}
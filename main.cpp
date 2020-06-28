#include <stdio.h>
#include <iostream>

#include "contoller.hpp"

int main( int argc, char* args[] )
{
    // Matter::Rectangle rectangle (20, 40);
    // Matter::Circle circle (20);

    // rectangle.collision_with(rectangle);
    // rectangle.collision_with(circle);
    // circle.collision_with(rectangle);
    // circle.collision_with(circle);


    Controller controller;
    controller.run();
}
#include <stdio.h>
#include <iostream>

#include "renderer.hpp"
#include "photon.hpp"
#include "universe.hpp"
#include "matter.hpp"

int main( int argc, char* args[] )
{
    Matter::Rectangle rectangle (0.0, 0.0);
    Matter::Circle circle (0.0);

    rectangle.collision_with(rectangle);
    rectangle.collision_with(circle);
    circle.collision_with(rectangle);
    circle.collision_with(circle);
}
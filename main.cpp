#include <stdio.h>
#include <iostream>

#include "renderer.hpp"
#include "photon.hpp"
#include "universe.hpp"
#include "matter.hpp"

int main( int argc, char* args[] )
{
    Matter::Rectangle rectangle (20, 40);
    Matter::Circle circle (20);

    rectangle.collision_with(rectangle);
    rectangle.collision_with(circle);
    circle.collision_with(rectangle);
    circle.collision_with(circle);

    Renderer renderer;
    Universe universe (renderer);

    Matter a (
        Vec3<float> (50, 50, 0),
        Vec3<float> (0),
        0,
        Matter::Circle(50)
    );
    Renderer::Rectangle gr_rect (20, 40);
    a.add_graphic(&gr_rect);
    universe.add_matter(a);

    Matter b (
        Vec3<float> (300, 300, 0),
        Vec3<float> (0),
        0,
        Matter::Rectangle(100, 50)
    );
    Renderer::Circle gr_circ (20);
    b.add_graphic(&gr_circ);
    universe.add_matter(b);

    renderer.init_window();
    universe.draw();

    // printf("Start sleeping...\n");
    // for(int i = 0; i < 1e10; i++){

    // }
    // printf("Done\n");
}
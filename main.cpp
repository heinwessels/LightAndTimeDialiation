#include <stdio.h>
#include <iostream>

#include "renderer.hpp"
#include "photon.hpp"

int main( int argc, char* args[] )
{
    Renderer renderer;

    for (int i = 0; i < 5; i++){
        Photon photon;
        photon.pos.x = i;
        renderer.add_sprite(photon);
    }

    renderer.draw_sprites();

}
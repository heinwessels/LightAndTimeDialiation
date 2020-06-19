#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <stdio.h>

#include "vec3.hpp"

class Sprite{
    public:

    Vec3<float> pos;

};

class Renderer{

    public:

    static const int max_num_of_sprites = 100;
    Sprite sprites [max_num_of_sprites];
    int num_of_sprites = 0;

    void add_sprite(Sprite sprite);


    void draw_sprites();

};


#endif
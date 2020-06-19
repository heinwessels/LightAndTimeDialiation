#include "renderer.hpp"


void Renderer::add_sprite(Sprite sprite){
    sprites[num_of_sprites++] = sprite;
}

void Renderer::draw_sprites(){
    for (int i = 0; i < num_of_sprites; i++)
        printf("%f\n", sprites[i].pos.x);
}
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>

#include "matter.hpp"
#include "renderer.hpp"

class Universe{

    private:

    class Observer{
        Vec3<float> pos;
        float scale;
    };

    static const int max_matter = 100;
    Matter * matter [max_matter];
    int num_of_matter = 0;

    Renderer *renderer;

    public:
    Universe(Renderer &r) : renderer(&r){};

    void step(double time);
    void handle_collisions();
    void draw();

    void add_matter(Matter &matter);
};

#endif
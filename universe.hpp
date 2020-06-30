#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>

#include "matter.hpp"
#include "renderer.hpp"

class Universe{
    public:
    Universe(Renderer &r) : renderer(&r){};
    ~Universe();

    class Observer{
    public:
        Vec3<double> *pos;   // Pointer in order to connect to matter (if required)
        Vec3<double> *speed; // Pointer in order to connect to matter (if required)
        float scale = 1;     // in meter per pixel
    };
    Observer observer;

    void step(double time);
    void handle_forces(double time);
    void handle_collisions();
    void draw();

    void add_matter(Matter *matter);

private:

    static const int max_matter = 100;
    Matter * matter [max_matter];
    int num_of_matter = 0;

    Renderer *renderer;
};

#endif
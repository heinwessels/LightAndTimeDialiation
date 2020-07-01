#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <vector>

#include "matter.hpp"
#include "renderer.hpp"

class Universe{
    public:
    Universe(Renderer &r) : renderer(&r), observer(r.screen_width, r.screen_height) {};
    ~Universe();

    class Observer{
    public:
        Vec3<double> screen_size;
        Vec3<double> *ref_pos = NULL;               // Pointer in order to connect to matter (if required)
        Vec3<double> cam_pos = Vec3<double>(0);     // Shift camera in pixels
        Vec3<double> *speed = NULL;                 // Pointer in order to connect to matter (if required)
        float scale = 1;                            // in meter per pixel
        Observer(int screen_width, int screen_height) : screen_size (screen_width, screen_width, 0) {};
        Vec3<double> get_screen_position(Vec3<double> pos){return pos * scale + screen_size / 2 + cam_pos;}
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
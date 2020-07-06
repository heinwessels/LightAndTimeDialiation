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
        float ref_scale = 1;                        // in meter per pixel
        float zoom = 1;
        Observer(int screen_width, int screen_height) : screen_size (screen_width, screen_width, 0) {};
        Vec3<double> get_screen_position(Vec3<double> pos){return pos * (ref_scale * zoom) + screen_size / 2 + cam_pos*zoom;}
        double get_scale_factor(){return ref_scale * zoom;}
        Vec3<double> get_universe_pos_from_screen(Vec3<double> pos){return (pos - cam_pos * zoom - screen_size / 2) / (ref_scale * zoom);}
    };
    Observer observer;

    void step(double time);
    void handle_forces(double time);
    void handle_collisions();
    void draw();

    void add_matter(Matter *matter);
    void clear_light_outside_boundary(Vec3<double> mininum, Vec3<double> maximum);
    void emit_light_from_point(Vec3<double> pos, double offset_radius, double amount);

    int get_num_of_matter(){return matter.size();}

    std::vector<Matter*> matter;
    Renderer *renderer;
};

#endif
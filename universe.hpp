#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <memory>
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
        Vec3<double> get_universe_pos_from_screen(Vec3<double> pos){return (pos - cam_pos * zoom - screen_size / 2) / (ref_scale * zoom);}
        double get_scale_factor(){return ref_scale * zoom;}
    };
    Observer observer;

    void step(double time);
    void handle_forces(double time);
    void handle_collisions();
    void draw();

    void add_matter(std::unique_ptr<Matter> matter);
    void clear_matter_outside_boundary(Vec3<double> mininum, Vec3<double> maximum);

    int get_num_of_matter(){return matter.size();}

    // STORAGE OF ALL MATTER
    // Using container of matter *pointers* to avoid slicing during polymorphism.
    // Using <std::unique_ptr> to automatically handle memory management
    std::vector<std::unique_ptr<Matter> > matter;


    Renderer *renderer;
};

#endif
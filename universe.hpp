#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <memory>
#include <vector>
#include <chrono>

#include "matter.hpp"
#include "renderer.hpp"

class Universe{
    public:
    Universe(Renderer &r) : renderer(&r), observer(r.screen_width, r.screen_height) {};
    ~Universe(){};

    class Observer{
    public:
        Vec3<double> screen_size;
        Vec3<double> *ref_pos = NULL;         // Pointer in order to connect to matter (if required, otherwise NULL)
        Vec3<double> cam_pos = Vec3<double>(0);     // Shift camera in pixels
        Vec3<double> *speed = NULL;                 // Pointer in order to connect to matter (if required)
        double simulation_speed = 60*60;          // In simulated seconds per second
        double time_step_max = 100;
        float ref_scale = 1;                        // in meter per pixel
        float zoom = 1;
        Observer(int screen_width, int screen_height) : screen_size (screen_width, screen_height, 0) {};
        Vec3<double> get_screen_position_from_universe(Vec3<double> uni_pos);
        Vec3<double> get_universe_pos_from_screen(Vec3<double> screen_pos);
        Vec3<double> get_universe_offset();
        double get_scale_factor(){return ref_scale * zoom;}
    };
    Observer observer;

    void step(double time);
    void handle_forces(double time);
    void handle_collisions();
    void draw();

    void add_matter(std::unique_ptr<Matter> matter);

    void clear_matter_outside_boundary(Vec3<double> mininum, Vec3<double> maximum);
    void add_trail_to_matter();

    int get_num_of_matter(){return matter.size();}
    Matter * get_matter_at_pos(Vec3<double> at);
    void camera_track_next_matter();

    // STORAGE OF ALL MATTER
    // Using container of matter *pointers* to avoid slicing during polymorphism.
    // Using <std::unique_ptr> to automatically handle memory management
    std::vector<std::unique_ptr<Matter> > matter;


    Renderer *renderer;
};

#endif
#ifndef MATTER_HPP
#define MATTER_HPP

#include "vec3.hpp"
#include "renderer.hpp"
// #include "universe.hpp"

class Matter{

    private:
    Graphic graphic;

    public:
    Vec3<float> pos;
    Vec3<float> speed;
    float weight;

    Matter();
    ~Matter();

    Matter(Vec3<float> pos, Vec3<float> speed, float weight);

    void add_graphic(Graphic graphic);

    // void step(Universe &universe);
};

class Photon : public Matter{

};

#endif
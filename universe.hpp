#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include "photon.hpp"

class Universe{

    private:
    static const int max_photons = 100;
    Photon photons [max_photons];
    int num_of_photons = 0;


};

#endif
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include "matter.hpp"

class Universe{

    private:
    static const int max_matter = 100;
    Matter matter [max_matter];
    int num_of_matter = 0;


};

#endif
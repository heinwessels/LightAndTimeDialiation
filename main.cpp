#include <stdio.h>
#include <iostream>

#include "contoller.hpp"
#include "physics.hpp"

int main( int argc, char* args[] )
{
    Controller controller;
    controller.init();
    controller.run();
}
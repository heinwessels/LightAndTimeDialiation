#include "universe_template.hpp"

void Template::sun_earth_moon(Universe &universe){
    // Create Sun
    auto sun = std::make_unique<Body>(
        (double)(1.9884e30),
        Vec3<double> (0, 0, 0),
        Vec3<double> (0, 0, 0),
        695700000
    );
    sun->graphic->colour = Renderer::Colour(255, 255, 0, 255);
    universe.add_matter(std::move(sun));

    // Create Earth
    auto earth = std::make_unique<Body>(
        (double)(6e24),
        Vec3<double> (149598023000/*0*/, 0, 0),
        Vec3<double> (0, 29780/*0*/, 0),
        6378100
    );
    universe.add_matter(std::move(earth)); // Move ownership from <earth> to function call

    // Create Moon
    // auto moon = std::make_unique<Body>(
    //     (double)(7.35e22),
    //     Vec3<double> (384400000, 0, 0),
    //     Vec3<double> (0, 0 /*1022*/, 0),
    //     1738100
    // );
    auto moon = std::make_unique<Body>(
        (double)(7.35e22),
        Vec3<double> (149598023000 + 384400000, 0, 0),
        Vec3<double> (0, 29780 + 1022, 0),
        1738100
    );
    moon->graphic->colour = Renderer::Colour(255, 255, 255, 255);
    universe.add_matter(std::move(moon));

    // Setup Observer
    universe.observer.ref_pos = new Vec3<double>(0);
    universe.observer.speed = new Vec3<double>(0);
    // universe->observer.ref_scale = (double)renderer->screen_width / (384400000 * 3);
    universe.observer.ref_scale = (double)universe.observer.screen_size.x / (149598023000 * 2.5);
}


void Template::gas_cloud(Universe &universe){

    int gseed = 5;
    int scale = 695700000*3;

    srand(gseed);

    // std::cout << "---------------------------------\n";
	// std::cout << "* frequency [0.1 .. 8.0 .. 64.0] \n";
	// std::cout << "* octaves   [1 .. 8 .. 16]       \n";
	// std::cout << "* seed      [0 .. 2^32-1]        \n";
	// std::cout << "---------------------------------\n";
    // perlin.accumulatedOctaveNoise2D_0_1(x / fx, y / fy, octaves)

    double size_frequency = 3;
    double size_octaves = 4;
    const siv::PerlinNoise size_perlin(gseed);
    const double size_fx = scale / size_frequency;
    const double size_fy = scale / size_frequency;

    double speed_frequency = 3;
    double speed_octaves = 3;
    const siv::PerlinNoise speed_perlin(gseed + 5);
    const double speed_fx = scale / speed_frequency;
    const double speed_fy = scale / speed_frequency;

    double density = 0.05;
    double minimim_mass = 1;
    double maximum_mass = 4;
    double spacing_multiplier = 7;
    double speed_multiplier = 100;

    double x_start = -1000, x_end = 2000;
    double y_start = -1000, y_end = 2000;
    double x = x_start, y = y_start;
    while (y < y_end){

        double mass_randomizer = size_perlin.normalizedOctaveNoise2D(x / size_fx, y / size_fy, size_octaves);
        double mass = (mass_randomizer + 1) * maximum_mass / 2;
        double radius = Body::get_radius_based_on_mass(mass);


        if (mass > minimim_mass && mass_randomizer > 0){

            // Im here.

            Body body (
                M_PI*radius*radius*density,
                radius,
                Vec3<float>(x, y, 0));

            double speed_randomizer = speed_perlin.normalizedOctaveNoise2D(x / speed_fx, y / speed_fy, speed_octaves) / 0.1;
            // double speed_randomizer = (rand()%200)/100.0 - 1.0;
            body.speed = Vec3<float>(
                sin(speed_randomizer * M_PI * 2) * size_randomizer * speed_multiplier,
                cos(speed_randomizer * M_PI * 2) * size_randomizer * speed_multiplier,
                0
            );

            bodies[num_of_bodies++] = body;

            // printf("[%d, %d]:\n\tRadius: %.3f\n\tSpeed Rand: %.3f\n", x, y, radius, speed_randomizer);

        }
        else
        {
            radius = minimim_mass;
        }

        x += spacing_multiplier * radius;
        if(x >= x_end){
            x = x_start;
            y += radius * spacing_multiplier;
        }
    }
}
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

    uint32_t gseed = 555;
    double x_start = -2e9, x_end = 2e9;
    double y_start = -2e9, y_end = 2e9;

    double scale = 5e9;

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
    double speed_octaves = 4;
    const siv::PerlinNoise speed_perlin(gseed + 5);
    const double speed_fx = scale / speed_frequency;
    const double speed_fy = scale / speed_frequency;

    double minimim_mass = 1e15;
    double maximum_mass = 5e25;
    double spacing_multiplier = 5e0;
    double speed_multiplier = 1e4;

    double x = x_start, y = y_start;
    double max_radius = 0;
    while (y < y_end){

        double mass_randomizer = size_perlin.normalizedOctaveNoise2D(x / size_fx, y / size_fy, size_octaves);
        double mass = minimim_mass + (mass_randomizer*5)* maximum_mass;
        double radius = Body::get_radius_based_on_mass(mass);

        if (radius > max_radius){max_radius = radius;}
        if (mass > minimim_mass && mass_randomizer > 0 && radius > 0){

            double speed_randomizer = speed_perlin.normalizedOctaveNoise2D(x / speed_fx, y / speed_fy, speed_octaves) / 0.1;
            universe.add_matter(std::make_unique<Body>(
                mass,
                Vec3<double> (x, y, 0),
                Vec3<double>(
                    sin(speed_randomizer * M_PI * 2) * mass_randomizer * speed_multiplier,
                    cos(speed_randomizer * M_PI * 2) * mass_randomizer * speed_multiplier,
                    0
                ),
                radius
            ));

        }
        else
        {
            radius = Body::get_radius_based_on_mass(maximum_mass);
        }

        x += spacing_multiplier * radius;
        if(x >= x_end){
            x = x_start;
            y += max_radius * spacing_multiplier;
            max_radius = 0;

            printf("Building: %.2f %%\t\t Number of bodies: %d\n", (y-y_start)/(y_end-y_start) * 100, universe.get_num_of_matter());
        }
    }

    // Setup Observer
    universe.observer.ref_pos = new Vec3<double>(0);
    universe.observer.speed = new Vec3<double>(0);
    universe.observer.ref_scale = (double)universe.observer.screen_size.x / (x_end - x_start);
}
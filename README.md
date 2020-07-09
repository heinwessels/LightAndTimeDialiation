# LightAndTimeDialiation
This project will simulate emitted light being bent by space-time, hopefully also showing light's change in frequency. However, the **goal** is to learn more about C++ and OOP best practices. This is my only second *real* C++ project that I'm designing, so I still have a lot to learn. The idea is to over-design everything to force the use of best practices that will typically be used for large commercial projects.

This software is based on the idea of a previous similar simulation I wrote called [UniverseSimulation](https://github.com/heinwessels/UniverseSimulator). However, that repo's code structure isn't well designed (being my first real C++ project), so the idea is to rewrite it and make it better designed and much cooler.

## Development Process
The process I during the development of this project is as follows:

1. **Design Class Structure with UML.** I first designed the class layout using UML, looking into best practices, etc. It gave me a good idea of what the problems are that I will have to solve and what tools are available (e.g. composition, polymorphism, etc.).
2. **Implement and Refine Structure.** I implemented the structure I thought would work, and then refined, redesiged, and restructured until the software was well rounded.
3. **Document Structure and Lessons Learned.** *(I'm here)* Before implementing the final physics, I wanted to document my findings and lessons learned while it's still fresh. I updated the UML diagram, and I'm working on *this* README.
4. **Add Relativity Physics.** *(TODO)* Add cool relativity physics to simulation to see how light bends and slow down, even though it has zero mass.

## Final Class Structure and UML

I designed the class structure using a UML diagram using LucidChart. I favoured composition over inheritance, for example `Matter` `has-a` `Graphic` and `CollisionBox`, rather than `is-a`. Although, I did find that `matter` inheriting `mass` made the code much cleaner and readable, which I believe is sometimes more important.

![UML Diagram](uml/uml_20200708.jpeg)

## Lessons Learned
- Having raw arrays of polymorphism objects is **really bad**, because it will cause slicing. The solution is to use a array of pointers, or even better, `std:unique_ptr`. This will ensure uncompromised memory, and no accidental memory leaks if used correctly. However, rather storing pointers is bad for caching, since the objects won't neccesarily be sequential in memory, but this is an optimization problem, and negligible in our case.
- There's little reason to use raw arrays. A container, e.g. `std::vector`, is just as efficient if used correctly, and has some powerful capabilities.
- Favour *composition* over *inheritance*. This makes the code more modular and future proof. However, *inheritance* still has it's benifits, such as readability.
- With derived classes `virtual` functions are very powerful and can make polymorhism very easy, intuitive and readable.
- Ideally base classes should not know about their derived classes, and the derived classes should not know about each other. This was hard to implement for `CollisionBox` and isn't perfect (they know a little), but was made easier by using a *Factory Pattern* and implementing a `CollisionHandler`.

## TODO
- Improve circle drawing algorithm to use Bresenham, if it's an issue in speed.
- Remove dependency between `Universe` and `Renderer`.
- Add cool physics.

## Improvements from previous Universe Simulation
- Simulation speed per second is constant, e.g. `200 seconds per second`. If the processing takes too long it will increase the time step per calculation to reduce the number of calculations, instead of limiting the amount calculations with a fixed time step. This will decrease the accuracy *slightly*, but it's negligible. This is an improvement from trying to reach a specific number of updates per second with a fixed timestep, meaning when the processing is slow, the simulation is slow.

## The Physics: Attempting to Simulate Space-Time
The goal of this simulation is to see the effect of the curvature of space-time on photons, or in simpler terms, see it slow down and bend in 3D space around heavy objects.

I am no physicist, so please take my research with a grain of salt.

### Description
Around heavy objects light will arguably do two things. It will **bend**, and it will **slow down**. These effects are explained by General Relativity, which states that heavy objects will *bend* the curvature of space *and* time.

Bending *space* means that the fabric of our universe is bent. An easy example of this is the recent famous picture of the black hole [Messier 87](https://en.wikipedia.org/wiki/File:Black_hole_-_Messier_87_crop_max_res.jpg). In this picure you can see the *other side* of the blackhole, even though light always travels in a straight line. This is because the intense gravity of the black hole actually *bends* the fabric of space around it, so although the light travels in a straight line, seems to go *around* the black hole. For reference, this effect cannot be explained by Newton's Gravitational Law, since photons have zero mass, which creates a zero force.

But according to General Relativity our universe has 4 dimentions, so it includes time! So if space is bent, then *time* will bent as well. And bending time means you change the *rate* of passing of time. This means for a distant observer, it will apear that light moves slower close to heavy objects, even though light always travel at the speed of light. What happens is that the light *is* travelling at the speed of light, but *time* passes more slowly in the vicinity of that light relative to the distant obeserver, which will make it *seem* like the light is travelling slower. A simple example of this is called the [Shapiro Time Delay](https://en.wikipedia.org/wiki/Shapiro_time_delay).

No, it just takes longer to move since there is more distance?

### Accurate Simulation


### Approximation

Gravitional lens

- Light is affected by gravity even though it has **zero mass**! A thought experiment called the Equivalence Principle reasons why this can be observed [here](https://astronomy.stackexchange.com/questions/29122/if-light-has-no-mass-why-is-it-affected-by-gravity). Einstein considered this experiment as his *Happiest Thought*. What really happens is that gravity bends *space time*, and light is traveling in a straight line on that bent path. There


Approximation at r >> schwartzchild radii and factor close to 1
https://astronomy.stackexchange.com/questions/14367/gravitational-time-dilation-multiple-sources

I need gravity potential!
https://astronomy.stackexchange.com/questions/27806/does-time-dilation-increase-within-overlapping-gravitational-fields

redshift of a radial photon emitted by someone on a circular orbit
https://physics.stackexchange.com/a/146683
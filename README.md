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

## Calculating Light Deflection and Slow Down
Gravitional lens

- Light is affected by gravity even though it has **zero mass**! A thought experiment called the Equivalence Principle reasons why this can be observed [here](https://astronomy.stackexchange.com/questions/29122/if-light-has-no-mass-why-is-it-affected-by-gravity). Einstein considered this experiment as his *Happiest Thought*. What really happens is that gravity bends *space time*, and light is traveling in a straight line on that bent path. There

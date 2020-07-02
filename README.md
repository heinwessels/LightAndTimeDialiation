# LightAndTimeDialiation
This project will simulate emitted light being bent by space-time, hopefully also showing light's change in frequency. The goal is to learn more about C++ OOP practices.


## Lessons Learned
- Objects should not contain their full graphic information. Rather just basic information about size, and the renderer should know how to draw it.


## Principles Used
- **UML Design:** The program was designed initially by a UML diagram, which was then kept up-to-date.
- **Polymorhism:** All objects in universe as stored as `Matter`, but could be `Body`, `Rocket` or `Photon` which has `Matter` as a base class.
- **Composition:**
  - Collisions of `Matter` is handled by the internal `Shape` variable, where `Shape` can be either `Rectangle` or `Circle` (with `Shape` as base class). Then calling e.g. `Shape::Rectangle.collision_with(?)` directs to the correct method in `Shape` to handle the collision.
- **Factory Pattern:**
  - Handle of shape collisions in Pyshics engine (TODO)

## Unsure
- Creation (using `new`) and deletion (using `delete`) of matter, collision boxes and graphics.

## TODO
- Improve circle drawing algorithm to use Bresenham.
- Write `step` function for `matter` so that photons don't need to do a gravity calculation.
- Remove photons that are too far away from the origin.
- Add strategic comments.

## Improvements from previous Universe Simulation
- Simulation speed per second is constant. If the processing takes too long it will increase the time step per calculation, instead of limiting the amount calculations with a fixed time step.

## Cool Physics Things
- Light is affected by gravity even though it has **zero mass**! A thought experiment called the Equivalence Principle reasons why this can be observed [here](https://astronomy.stackexchange.com/questions/29122/if-light-has-no-mass-why-is-it-affected-by-gravity). Einstein considered this experiment as his *Happiest Thought*. What really happens is that gravity bends *space time*, and light is traveling in a straight line on that bent path. There


## Calculating Light Deflection and Slow Down
Gravitional lens

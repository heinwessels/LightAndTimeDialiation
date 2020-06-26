# LightAndTimeDialiation
This project will simulate emitted light being bent by space-time, hopefully also showing light's change in frequency. The goal is to learn more about C++ OOP practices.


## Lessons Learned
- Objects should not contain their full graphic information. Rather just basic information about size, and the renderer should know how to draw it.


## Principles Used
- **UML Design:** The program was designed initially by a UML diagram, which was then kept up-to-date.
- **Polymorhism:** All objects in universe as stored as `Matter`, but could be `Body`, `Rocket` or `Photon` which has `Matter` as a base class.
- **Composition:**
  - Collisions of `Matter` is handled by the internal `Shape` variable, where `Shape` can be either `Rectangle` or `Circle` (with `Shape` as base class). Then calling e.g. `Shape::Rectangle.collision_with(?)` directs to the correct method in `Shape` to handle the collision.
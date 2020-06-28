#include "physics.hpp"

bool Physics::CollisionHandler::collision_between_rectangle_and_rectangle(const Rectangle &rectangle1, const Rectangle &rectangle2){
    printf("Collision between rectangle and rectangle\n");
    return false;
}
bool Physics::CollisionHandler::collision_between_rectangle_and_circle(const Rectangle &rectangle, const Circle &circle){
    printf("Collision between rectangle and circle\n");
    return false;
}
bool Physics::CollisionHandler::collision_between_circle_and_circle(const Circle &circle1, const Circle &circle2){
    printf("Collision between circle and circle\n");
    return false;
}

bool Physics::Rectangle::collision_with(Physics::CollisionBox *box){
    // This doesn't follow DRY, and derived classes needs to know of each other.
    if (Physics::Rectangle* rectangle = dynamic_cast<Physics::Rectangle*>(box)){
       return CollisionHandler::collision_between_rectangle_and_rectangle(*this, *rectangle);
    } else {
       return CollisionHandler::collision_between_rectangle_and_circle(*this, *dynamic_cast<Physics::Circle*>(box));
    }
}
bool Physics::Circle::collision_with(Physics::CollisionBox *box){
    // This doesn't follow DRY, and derived classes needs to know of each other.
    if (Physics::Rectangle* rectangle = dynamic_cast<Physics::Rectangle*>(box)){
       return CollisionHandler::collision_between_rectangle_and_circle(*rectangle, *this);
    } else {
       return CollisionHandler::collision_between_circle_and_circle(*this, *dynamic_cast<Physics::Circle*>(box));
    }
}
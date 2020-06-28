#include "physics.hpp"

bool Physics::CollisionHandler::collision_between_rectangle_and_rectangle(Rectangle &rectangle1, Rectangle &rectangle2){
    if (rectangle1.pos == NULL || rectangle2.pos == NULL){
        printf("ERROR! Collision box's position was not defined!\n");
        throw;
    }
    return  (rectangle1.pos->x - rectangle1.width / 2 )     < (rectangle2.pos->x + rectangle2.width / 2) &&
            (rectangle1.pos->x + rectangle1.width / 2 )     > (rectangle2.pos->x - rectangle2.width / 2) &&
            (rectangle1.pos->y - rectangle1.height / 2 )    < (rectangle2.pos->y + rectangle2.height / 2) &&
            (rectangle1.pos->y + rectangle1.height / 2 )    > (rectangle2.pos->y - rectangle2.height / 2);
}
bool Physics::CollisionHandler::collision_between_rectangle_and_circle(Rectangle &rectangle, Circle &circle){
    if (rectangle.pos == NULL || circle.pos == NULL){
        printf("ERROR! Collision box's position was not defined!\n");
        throw;
    }
    double  dx = abs(circle.pos->x - rectangle.pos->x) - rectangle.width / 2,
            dy = abs(circle.pos->y - rectangle.pos->y) - rectangle.height / 2;
    if (dx > circle.radius || dy > circle.radius) { return false; }
    if (dx <= 0 || dy <= 0) { return true; }
    return (dx * dx + dy * dy <= circle.radius * circle.radius);
}
bool Physics::CollisionHandler::collision_between_circle_and_circle(Circle &circle1, Circle &circle2){
    if (circle1.pos == NULL || circle2.pos == NULL){
        printf("ERROR! Collision box's position was not defined!\n");
        throw;
    }
    return (circle1.pos->x-circle2.pos->x)*(circle1.pos->x-circle2.pos->x) + (circle1.pos->y-circle2.pos->y)*(circle1.pos->y-circle2.pos->y)
            < (circle1.radius + circle2.radius)*(circle1.radius + circle2.radius);
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
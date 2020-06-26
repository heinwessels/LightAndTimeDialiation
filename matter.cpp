#include "matter.hpp"


bool Matter::Shape::collision_between_rectangle_and_rectangle(const Rectangle &rectangle1, const Rectangle &rectangle2){
    printf("Collision between rectangle and rectangle\n");
    return false;
}
bool Matter::Shape::collision_between_rectangle_and_circle(const Rectangle &rectangle, const Circle &circle){
    printf("Collision between rectangle and circle\n");
    return false;
}
bool Matter::Shape::collision_between_circle_and_circle(const Circle &circle1, const Circle &circle2){
    printf("Collision between circle and circle\n");
    return false;
}

bool Matter::Rectangle::collision_with(const Rectangle &rectangle){
    return Shape::collision_between_rectangle_and_rectangle(*this, rectangle);
}
bool Matter::Rectangle::collision_with(const Circle &circle){
    return Shape::collision_between_rectangle_and_circle(*this, circle);
}
bool Matter::Circle::collision_with(const Rectangle &rectangle){
    return Shape::collision_between_rectangle_and_circle(rectangle, *this);
}
bool Matter::Circle::collision_with(const Circle &circle){
    return Shape::collision_between_circle_and_circle(*this, circle);;
}
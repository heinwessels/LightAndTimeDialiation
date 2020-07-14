#include "physics.hpp"

bool Physics::CollisionHandler::collision_between_rectangle_and_rectangle(
    Vec3<double> rect1_pos, const Physics::Rectangle &rect1,
    Vec3<double> rect2_pos, const Physics::Rectangle &rect2
){
    return  (rect1_pos.x - rect1.width / 2 )     < (rect2_pos.x + rect2.width / 2) &&
            (rect1_pos.x + rect1.width / 2 )     > (rect2_pos.x - rect2.width / 2) &&
            (rect1_pos.y - rect1.height / 2 )    < (rect2_pos.y + rect2.height / 2) &&
            (rect1_pos.y + rect1.height / 2 )    > (rect2_pos.y - rect2.height / 2);
}
bool Physics::CollisionHandler::collision_between_rectangle_and_circle(
    Vec3<double> rect_pos, const Physics::Rectangle &rect,
    Vec3<double> circ_pos, const Physics::Circle &circ
){
    double  dx = abs(circ_pos.x - rect_pos.x) - rect.width / 2,
            dy = abs(circ_pos.y - rect_pos.y) - rect.height / 2;
    if (dx > circ.radius || dy > circ.radius) { return false; }
    if (dx <= 0 || dy <= 0) { return true; }
    return (dx * dx + dy * dy <= circ.radius * circ.radius);
}
bool Physics::CollisionHandler::collision_between_circle_and_circle(
    Vec3<double> circ1_pos, const Physics::Circle &circ1,
    Vec3<double> circ2_pos, const Physics::Circle &circ2
){
    return (circ1_pos.x-circ2_pos.x)*(circ1_pos.x-circ2_pos.x) + (circ1_pos.y-circ2_pos.y)*(circ1_pos.y-circ2_pos.y)
            < (circ1.radius + circ2.radius)*(circ1.radius + circ2.radius);
}

bool Physics::Rectangle::collision_with(Vec3<double> this_pos, Vec3<double> other_pos, CollisionBox *other_box){
    // This doesn't follow DRY, and derived classes needs to know of each other.
    if (other_box->is_rectangle()){
       return CollisionHandler::collision_between_rectangle_and_rectangle(this_pos, *this, other_pos, *static_cast<Physics::Rectangle*>(other_box));
    } else {
       return CollisionHandler::collision_between_rectangle_and_circle(this_pos, *this, other_pos, *static_cast<Physics::Circle*>(other_box));
    }
}
bool Physics::Circle::collision_with(Vec3<double> this_pos, Vec3<double> other_pos, CollisionBox *other_box){
    // This doesn't follow DRY, and derived classes needs to know of each other.
    if (other_box->is_rectangle()){
       return CollisionHandler::collision_between_rectangle_and_circle(this_pos, *static_cast<Physics::Rectangle*>(other_box), other_pos, *this);
    } else {
       return CollisionHandler::collision_between_circle_and_circle(this_pos, *this, other_pos, *static_cast<Physics::Circle*>(other_box));
    }
}

void Physics::Mass::apply_force(Vec3<double> force){
    force_applied += force; // The force will applied to the mass when <step> is called
}
void Physics::Mass::step(double time){

    Vec3<double> force_to_apply = force_base + force_applied;
    // First make sure there's sufficient mass to calculate acceleration,
    // and that theres an actual force applied
    if (mass > 1e-6 && (
        (force_to_apply.x != 0 || force_to_apply.y != 0 || force_to_apply.z != 0)
    )){
        Vec3<double> acceleration = (force_base + force_applied) / mass;
        speed += acceleration * time;   // The next formule uses the final speed
        pos += speed * time - (acceleration * 0.5 * time * time);

        // Now clear the <force_applied> since it's been handled
        force_applied = Vec3<double> (0.0);
    }
    else{
        // Can't accelerate object using force with no mass
        pos += speed * time;
    }
}

Vec3<double> Physics::Mass::newtonian_gravitational_force_to(Physics::Mass &other){
    Vec3<double> dpos = other.pos - this->pos;
    float r3 = dpos.x*dpos.x + dpos.y*dpos.y;
    r3 *=  sqrt(r3);
    float f = G * mass * other.mass / r3;
    return Vec3<double>(f * dpos.x, f * dpos.y, 0);
}
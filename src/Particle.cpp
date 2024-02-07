#include "Particle.h"
#include "Physics.h"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <cstdio>

Particle::Particle(sf::Vector2<float> initial_position,
                   sf::Vector2<float> initial_velocity,
                   sf::Vector2<float> acceleration_,
                   float dt,
                   float radius_,
                   sf::Color color_) {
    prev_position = set_prev_position(
        initial_position, initial_velocity, acceleration_, dt);
    position = initial_position;
    acceleration = acceleration_;
    radius = radius_;
    color = color_;
}

sf::Vector2<float> set_prev_position(sf::Vector2<float> initial_position,
                                     sf::Vector2<float> initial_velocity,
                                     sf::Vector2<float> acceleration_,
                                     float dt) {
    return sf::Vector2<float>(
        Verlet::previous_position(
            initial_position.x, initial_velocity.x, acceleration_.x, dt),
        Verlet::previous_position(
            initial_position.y, initial_velocity.y, acceleration_.y, dt));
}

void Particle::update_pos(float dt) {
    auto _prev_position = prev_position;
    prev_position = position;
    position.x =
        Verlet::next_position(_prev_position.x, position.x, acceleration.x, dt);
    position.y =
        Verlet::next_position(_prev_position.y, position.y, acceleration.y, dt);
    prev_dt = dt;
}

sf::CircleShape Particle::get_shape() {
    sf::CircleShape shape = sf::CircleShape(radius);
    shape.setFillColor(color);
    shape.setPosition(position.x - radius, position.y - radius);
    return shape;
}

void Particle::handle_surface_collision(sf::RectangleShape box) {
    // collision against left and right walls
    if (position.x - radius < box.getPosition().x) {
        resolve_collision(
            position.x, prev_position.x, box.getPosition().x + radius);
    } else if (position.x + radius >= box.getPosition().x + box.getSize().x) {
        resolve_collision(position.x,
                          prev_position.x,
                          box.getPosition().x + box.getSize().x - radius);
    }

    if (position.y - radius <= box.getPosition().y) {
        resolve_collision(
            position.y, prev_position.y, box.getPosition().y + radius);
    } else if (position.y + radius >= box.getPosition().y + box.getSize().y) {
        resolve_collision(position.y,
                          prev_position.y,
                          box.getPosition().y + box.getSize().y - radius);
    }
}

void resolve_collision(float &x, float &prev_x, float reset_pos) {
    float x_ = x;
    // reset ball position
    x = reset_pos;
    // move previous position so that velocity changes signs
    // but keeps its magnitude
    prev_x = x - (prev_x - x_);
}

void Particle::handle_particle_collision(Particle &particle) {
    // check if they aren´t the same particle
    if (position == particle.position &&
        prev_position == particle.prev_position)
        return;

    float dst_sqr = Math::distance_sqr(position, particle.position);
    if (dst_sqr < (radius + particle.radius) * (radius + particle.radius)) {
        //  *-----------r1-(-overlap-)--r2------------*
        float dst = sqrtf(dst_sqr);
        float overlap = radius + particle.radius - dst;
        // delta positions are proportionate to the radiuses
        float delta_p1 = overlap * radius / (radius + particle.radius);
        float delta_p2 = overlap * particle.radius / (radius + particle.radius);

        // make a delta p1 vector and add it to p1
        auto p1_to_p2 = particle.position - position;
        auto normal_p1_to_p2 = Math::normalize_vector(p1_to_p2);
        printf("(%f, %f) |%f|\n", p1_to_p2.x, p1_to_p2.y, dst);
        printf("delta p1: %f\n", delta_p1);

        auto delta_p1_vec = normal_p1_to_p2 * delta_p1 * (-1.0f);

        // reflect previous position of p1
        auto prev_pos1_vec = prev_position - position;
        auto prev_pos1_projection =
            normal_p1_to_p2 * Math::dot_product(prev_pos1_vec, normal_p1_to_p2);
        // prev_position -= (prev_pos1_projection * 2.0f);
        prev_pos1_vec -= prev_pos1_projection;
        prev_position = position + prev_pos1_vec;

        position += delta_p1_vec;

        // prev_position = position;

        // make a delta p2 vector and add it to p2
        auto p2_to_p1 = position - particle.position;
        auto normal_p2_to_p1 = Math::normalize_vector(p2_to_p1);
        auto delta_p2_vec = normal_p2_to_p1 * delta_p2 * (-1.0f);

        // reflect previous position of p2
        auto prev_pos2_vec = particle.prev_position - position;
        auto prev_pos2_projection =
            normal_p2_to_p1 * Math::dot_product(prev_pos2_vec, normal_p2_to_p1);
        // particle.prev_position -= (prev_pos2_projection * 2.0f);
        prev_pos2_vec -= prev_pos2_projection;
        particle.prev_position = particle.position + prev_pos2_vec;

        particle.position += delta_p2_vec;
        // particle.prev_position = particle.position;

        dst_sqr = Math::distance_sqr(position, particle.position);
        printf("new distance: %f\n", sqrtf(dst_sqr));
    }
}

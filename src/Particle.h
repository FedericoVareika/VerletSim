#pragma once

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"

class Particle {
  public:
    Particle(sf::Vector2<float> initial_position,
             sf::Vector2<float> initial_velocity,
             sf::Vector2<float> acceleration,
             float dt,
             float radius_,
             sf::Color color_);

    // sf::Vector2<float> set_prev_position(sf::Vector2<float>
    // initial_velocity);
    void update_pos(float dt);
    sf::CircleShape get_shape();
    void handle_surface_collision(sf::RectangleShape box);
    void handle_particle_collision(Particle &particle);

  private:
    sf::Vector2<float> prev_position;
    sf::Vector2<float> position;
    // sf::Vector2<float> velocity;
    sf::Vector2<float> acceleration;
    float prev_dt;

    float radius;
    sf::Color color;
};

sf::Vector2<float> set_prev_position(sf::Vector2<float> initial_position,
                                     sf::Vector2<float> initial_velocity,
                                     sf::Vector2<float> acceleration_,
                                     float dt);
void resolve_collision(float &x, float &prev_x, float reset_pos);

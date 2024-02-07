#pragma once

#include "Particle.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>

class Simulation {
  public:
    float time;
    float dt;
    sf::Vector2<float> acceleration;

    Simulation(sf::RenderWindow *window_,
               float dt,
               sf::Vector2<float> acceleration_,
               int iterations_);

    void add_particle(const Particle &particle);
    void add_particle(sf::Vector2<float> position,
                      sf::Vector2<float> initial_velocity,
                      float radius,
                      sf::Color color);
    void update();
    void render();

    void setup_box(float width, float height, float x, float y);

  private:
    sf::RenderWindow *window;
    sf::RectangleShape box;

    std::vector<Particle> particles;
    int iterations;
};

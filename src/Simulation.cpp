#include "Simulation.h"
#include "Particle.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <vector>

Simulation::Simulation(sf::RenderWindow *window_,
                       float dt_,
                       sf::Vector2<float> acceleration_,
                       int iterations_) {
    window = window_;
    dt = dt_;
    acceleration = acceleration_;
    iterations = iterations_;
    time = 0;
}

void Simulation::add_particle(const Particle &particle) {
    particles.insert(particles.begin(), particle);
}

void Simulation::add_particle(sf::Vector2<float> position,
                              sf::Vector2<float> velocity,
                              float radius,
                              sf::Color color) {
    Particle particle =
        Particle(position, velocity, acceleration, dt, radius, color);
    particles.insert(particles.begin(), particle);
}

void Simulation::update() {
    time += dt;
    for (int i = 0; i < iterations; i++) {
        for (int i = 0; i < particles.size(); i++) {
            auto &p1 = particles.at(i);
            p1.update_pos(dt / iterations);
            p1.handle_surface_collision(box);

            for (int i = 0; i < particles.size(); i++) {
                auto &p2 = particles.at(i);
                p1.handle_particle_collision(p2);
            }
        }
    }
}
void Simulation::render() {
    window->clear();
    window->draw(box);
    for (Particle p : particles) {
        window->draw(p.get_shape());
    }
    window->display();
}

void Simulation::setup_box(float width, float height, float x, float y) {
    box = sf::RectangleShape(sf::Vector2<float>(width, height));
    box.setPosition(x, y);
}

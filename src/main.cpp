#include "Physics.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"
#include "Simulation.h"
#include <SFML/Graphics.hpp>
#include <cmath>

static sf::Color getRainbow(float t) {
    const float r = sin(t);
    const float g = sin(t + 0.33f * 2.0f * Math::PI);
    const float b = sin(t + 0.66f * 2.0f * Math::PI);
    return {static_cast<uint8_t>(255.0f * r * r),
            static_cast<uint8_t>(255.0f * g * g),
            static_cast<uint8_t>(255.0f * b * b)};
}

int main() {
    auto window = sf::RenderWindow{{1080u, 700u}, "CMake SFML Project"};
    window.setFramerateLimit(144);

    Simulation simulation =
        Simulation(&window, 1.0f / 60.0f, sf::Vector2<float>(0.0f, 100.0f), 8);
    simulation.setup_box(1000, 620, 40, 40);

    float x, y = 0;
    float clock = 0;
    float time_between_spawn = 0.1;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed &&
                       event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                auto mouse_pos = sf::Mouse::getPosition(window);
                x = mouse_pos.x;
                y = mouse_pos.y;
            } else if (event.type == sf::Event::MouseButtonReleased) {
                auto mouse_pos = sf::Mouse::getPosition(window);
                simulation.add_particle(
                    sf::Vector2<float>(x, y),
                    sf::Vector2<float>(x - mouse_pos.x, y - mouse_pos.y),
                    10.0f,
                    sf::Color(255, 120, 120, 255));
            }
        }

        clock += simulation.dt;
        if (clock >= time_between_spawn) {
            simulation.add_particle(
                sf::Vector2<float>(window.getSize().x / 2.0f,
                                   window.getSize().y / 2.0f),
                sf::Vector2<float>(Math::PI * sin(simulation.time),
                                   cos(Math::PI * simulation.time)),
                10.0f,
                // sf::Color(255, 120, 255, 255));
                getRainbow(simulation.time));
            clock = 0;
        }
        simulation.update();
        simulation.render();
    }
}
// simulation.add_particle(
//     sf::Vector2<float>(mouse_pos.x, mouse_pos.y),
//     sf::Vector2<float>(0, 0),
//     10.0f,
//     sf::Color(255, 120, 120, 255));

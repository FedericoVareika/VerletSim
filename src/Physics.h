#pragma once

#include "SFML/System/Vector2.hpp"
namespace Verlet {
float previous_position(float position,
                        float velocity,
                        float acceleration,
                        float dt);

float next_position(float prev_position,
                    float position,
                    float acceleration,
                    float dt);
}; // namespace Verlet

namespace Collision {}; // namespace Collision

namespace Math {
const float PI = 3.14159;
float distance_sqr(sf::Vector2<float> pos1, sf::Vector2<float> pos2);
sf::Vector2<float> normalize_vector(sf::Vector2<float> vec);
float dot_product(sf::Vector2<float> vec1, sf::Vector2<float> vec2);
} // namespace Math

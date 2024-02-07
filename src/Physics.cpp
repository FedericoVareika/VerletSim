#include "Physics.h"
#include "SFML/System/Vector2.hpp"
#include <cmath>

float Verlet::previous_position(float position,
                                float velocity,
                                float acceleration,
                                float dt) {
    return position - velocity * dt - acceleration * dt * dt;
}

float Verlet::next_position(float prev_position,
                            float position,
                            float acceleration,
                            float dt) {
    return 2 * position - prev_position + acceleration * dt * dt;
}

float Math::distance_sqr(sf::Vector2<float> pos1, sf::Vector2<float> pos2) {
    return (pos2.x - pos1.x) * (pos2.x - pos1.x) +
           (pos2.y - pos1.y) * (pos2.y - pos1.y);
}

sf::Vector2<float> Math::normalize_vector(sf::Vector2<float> vec) {
    float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y);
    return sf::Vector2<float>(vec.x / magnitude, vec.y / magnitude);
}

float Math::dot_product(sf::Vector2<float> vec1, sf::Vector2<float> vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

#include "globals.h"

sf::Vector2f normalise(const sf::Vector2f& vec)
{
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0)
        return vec / length;
    return sf::Vector2f(0.f, 0.f);
}

float getMagnitude(const sf::Vector2f& vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f randomPosition(const sf::Vector2f& vec)
{
    std::random_device random;
    std::mt19937 randomInstance(random());
    std::uniform_real_distribution<float> distX(0.f, vec.x);
    std::uniform_real_distribution<float> distY(0.f, vec.y);

    float randomX = distX(randomInstance);
    float randomY = distY(randomInstance);

    return sf::Vector2f(randomX, randomY);
}



#include "EnemyBehaviours.h"

sf::Vector2f EnemyBehaviours::calculateSeek(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, float speed)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    return normalize(direction) * speed;
}

float EnemyBehaviours::calculateRotation(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition)
{
    sf::Vector2f direction = targetPosition - currentPosition;
    float angleInRadians = std::atan2(direction.y, direction.x);
    float angleInDegrees = angleInRadians * 180.f / 3.14159f;
    return angleInDegrees;
}

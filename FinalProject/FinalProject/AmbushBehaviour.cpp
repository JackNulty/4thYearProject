#include "AmbushBehaviour.h"

void AmbushBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f direction = playerPos - enemy.getPos();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 25) {
        direction /= length;
        enemy.m_velocity += direction * 0.9f; 
    }
}

#include "FleeBehaviour.h"
#include "Enemy.h"

void FleeBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f direction = enemy.getPos() - playerPos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 25) {
        direction /= length;
        enemy.m_velocity += direction * 1.0f;
    }
}

std::unique_ptr<Behaviour> FleeBehaviour::clone() const
{
	return std::make_unique<FleeBehaviour>(*this);
}

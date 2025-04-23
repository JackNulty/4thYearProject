#include "CirclePointBehaviour.h"
#include "Enemy.h"

void CirclePointBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f dir = m_target - enemy.getPos();
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
    enemy.m_velocity += dir * 0.5f;
}

std::unique_ptr<Behaviour> CirclePointBehaviour::clone() const
{
	return std::make_unique<CirclePointBehaviour>(*this);
}

#include "SeekBehaviour.h"
#include "Enemy.h"

void SeekBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f dir = playerPos - enemy.getPos();
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0) dir /= length;
    enemy.m_velocity += dir * 0.5f;
}

std::unique_ptr<Behaviour> SeekBehaviour::clone() const
{
	return std::make_unique<SeekBehaviour>(*this);
}

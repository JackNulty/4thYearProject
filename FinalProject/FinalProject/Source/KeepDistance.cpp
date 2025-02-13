#include "KeepDistance.h"
#include "Enemy.h"

void KeepDistance::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f dir = enemy.getPos() - playerPos;
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if(length < 100.0f && length != 0)
	{
		dir /= length;
		enemy.m_velocity += dir * 0.5f;
	}
	else
	{
		enemy.m_velocity *= 0.9f;
	}

}

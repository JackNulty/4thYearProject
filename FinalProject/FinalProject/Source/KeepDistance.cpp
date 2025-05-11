#include "KeepDistance.h"
#include "Enemy.h"

void KeepDistance::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2f direction = enemy.getPos() - playerPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length < 200.0f && length != 0)
    {
        direction /= length;

        enemy.m_velocity += direction * 0.5f;
    }
    else if (length > 200.0f)
    {
        direction /= length;
        enemy.m_velocity -= direction * 0.5f;
    }
    else
    {
        enemy.m_velocity *= 0.9f;
    }
}

std::unique_ptr<Behaviour> KeepDistance::clone() const
{
	return std::make_unique<KeepDistance>(*this);
}

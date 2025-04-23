#include "Enemy.h"
#include "Behaviour.h"

Enemy::Enemy(float x, float y, float speed)
	: m_speed(speed)
{
	m_sprite.setPosition(x, y);
}

void Enemy::render(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Enemy::setBehaviour(std::unique_ptr<Behaviour> newBehaviour)
{
	m_behaviour = std::move(newBehaviour);
}

std::unique_ptr<Behaviour> Enemy::cloneBehaviour() const
{
	if (m_behaviour)
		return m_behaviour->clone();
	else
		return nullptr;
}

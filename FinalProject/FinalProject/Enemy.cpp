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

sf::FloatRect Enemy::getBounds() const
{
	return m_sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPos() const
{
	return m_sprite.getPosition();
}

void Enemy::setPos(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Enemy::setBehaviour(std::unique_ptr<Behaviour> newBehaviour)
{
	m_behaviour = std::move(newBehaviour);
}

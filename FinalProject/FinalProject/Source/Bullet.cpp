#include "Bullet.h"

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f direction, float speed)
	:m_direction(direction), m_speed(speed)
{
	m_bulletShape.setPosition(playerPos);
	m_bulletShape.setRadius(5);
}

void Bullet::update(float deltaTime)
{
	m_bulletShape.move(m_direction * m_speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(m_bulletShape);
}

bool Bullet::checkBounds()
{
	// check if the bullet is out of bounds based on the game size
	sf::Vector2f currentPos = m_bulletShape.getPosition();
	return currentPos.x < 0 || currentPos.x > WINDOW_WIDTH || currentPos.y < 0 || currentPos.y > WINDOW_WIDTH;
}

sf::FloatRect Bullet::getBounds() const
{
	return m_bulletShape.getGlobalBounds();
}

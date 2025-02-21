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

bool Bullet::checkBounds(const sf::View& cameraView)
{
	// check if the bullet is out of bounds based on the game size
	sf::Vector2f currentPos = m_bulletShape.getPosition();
	// Get the current view boundaries
	sf::Vector2f viewCenter = cameraView.getCenter();
	sf::Vector2f viewSize = cameraView.getSize();

	float left = viewCenter.x - (viewSize.x / 2);
	float right = viewCenter.x + (viewSize.x / 2);
	float top = viewCenter.y - (viewSize.y / 2);
	float bottom = viewCenter.y + (viewSize.y / 2);

	// Check if arrow is outside the current view bounds
	return currentPos.x < left - 50 || currentPos.x > right + 50 ||
		currentPos.y < top - 50 || currentPos.y > bottom + 50;
}

sf::FloatRect Bullet::getBounds() const
{
	return m_bulletShape.getGlobalBounds();
}

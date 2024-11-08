#include "Bullet.h"

Bullet::Bullet(sf::Vector2f playerPos, sf::Vector2f direction, float speed)
	:direction(direction), speed(speed)
{
	bulletShape.setPosition(playerPos);
	bulletShape.setRadius(5);
}

void Bullet::update(float deltaTime)
{
	bulletShape.move(direction * speed * deltaTime);
}

void Bullet::draw(sf::RenderWindow& window)
{
	window.draw(bulletShape);
}

bool Bullet::checkBounds()
{
	// check if the bullet is out of bounds based on the game size
	sf::Vector2f currentPos = bulletShape.getPosition();
	return currentPos.x < 0 || currentPos.x > WINDOW_WIDTH || currentPos.y < 0 || currentPos.y > WINDOW_WIDTH;
}

sf::FloatRect Bullet::getBounds() const
{
	return bulletShape.getGlobalBounds();
}

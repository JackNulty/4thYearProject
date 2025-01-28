#include "Arrow.h"

Arrow::Arrow(sf::Texture* arrowTexture, sf::Vector2f playerPos, float speed, sf::Vector2f direction, float rotation)
	:m_speed(speed), m_direction(direction)
{
	m_arrowSprite.setTexture(*arrowTexture);
	m_arrowSprite.setTextureRect(sf::IntRect(60, 3, 4, 13));
	m_arrowSprite.setOrigin(m_arrowSprite.getGlobalBounds().width / 2, m_arrowSprite.getGlobalBounds().height / 2);
	m_arrowSprite.setScale(2.0f, 2.0f);
	m_arrowSprite.setPosition(playerPos);
	m_arrowSprite.setRotation(rotation);
}

void Arrow::update(float deltaTime)
{
}

void Arrow::fixedUpdate(float deltaTime)
{
	m_arrowSprite.move(m_direction * m_speed * deltaTime);
}

void Arrow::render(sf::RenderWindow& window)
{
	window.draw(m_arrowSprite);
}

bool Arrow::checkBounds()
{
	sf::Vector2f currentPos = m_arrowSprite.getPosition();
	return currentPos.x < 0 || currentPos.x > WINDOW_WIDTH || currentPos.y < 0 || currentPos.y > WINDOW_WIDTH;
}

sf::FloatRect Arrow::getBounds() const
{
	return m_arrowSprite.getGlobalBounds();
}

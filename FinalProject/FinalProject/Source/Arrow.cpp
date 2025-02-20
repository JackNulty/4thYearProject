#include "Arrow.h"

Arrow::Arrow(sf::Vector2f playerPos, float speed, sf::Vector2f direction, float rotation)
	:m_speed(speed), m_direction(direction)
{
	if (!bowTexture.loadFromFile("Assets/Weapons/Bow_Stages.png"))
	{
		std::cout << "Error loading bow texture" << std::endl;
	}
	m_arrowSprite.setTexture(bowTexture);
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

bool Arrow::checkBounds(const sf::View& cameraView)
{
	sf::Vector2f currentPos = m_arrowSprite.getPosition();
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

sf::FloatRect Arrow::getBounds() const
{
	return m_arrowSprite.getGlobalBounds();
}

#include "Bow.h"

Bow::Bow()
{
	if(!m_bowTexture.loadFromFile("Assets/Weapons/Bow_Stages.png"))
	{
		std::cout << "Error loading bow texture" << std::endl;
	}
	m_bowSprite.setTexture(m_bowTexture);
	m_bowSprite.setTextureRect(sf::IntRect(10, 0, 6, 16));
	m_bowSprite.setOrigin(m_bowSprite.getGlobalBounds().width / 2, m_bowSprite.getGlobalBounds().height / 2);
	m_bowSprite.setPosition(100, 100);
	m_bowSprite.setScale(2, 2);

	//bow animation frames
	m_bowFrames.push_back(sf::IntRect(10, 0, 6, 16));
	m_bowFrames.push_back(sf::IntRect(17, 0, 12, 16));
	m_bowFrames.push_back(sf::IntRect(30, 0, 11, 16));
}

void Bow::render(sf::RenderWindow& window)
{
	window.draw(m_bowSprite);
}

void Bow::update(float deltaTime, sf::Vector2f playerPos)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		isActive = true;
	}
	if (isActive)
	{
		m_bowSprite.setPosition(playerPos);
	}
	else if (!isActive)
	{
		m_bowSprite.setPosition(-1000000, -100);
	}
}

void Bow::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAnimating)
	{
		isAnimating = true;
		currentFrame = 0;
		frameCounter = 0;
	}
	if (isAnimating)
	{
		animateBow();
	}

	rotateAroundPlayer(playerPos, mousePos);
}

void Bow::animateBow()
{
	// draw animation
	frameCounter++;
	if (frameCounter >= frameDelay)
	{
		frameCounter = 0;
		currentFrame++;
		if (currentFrame >= m_bowFrames.size())
		{
			currentFrame = 0;
			isAnimating = false;
		}
		m_bowSprite.setTextureRect(m_bowFrames[currentFrame]);
	}
}

void Bow::rotateAroundPlayer(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	sf::Vector2f direction = mousePos - playerPos;
	float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (mag != 0)
	{
		direction /= mag;
	}
	float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;
	m_bowSprite.setRotation(angle);
}

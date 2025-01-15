#include "Bow.h"

Bow::Bow()
{
	if(!m_bowTexture.loadFromFile("Assets/Weapons/Bow_Stages.png"))
	{
		std::cout << "Error loading bow texture" << std::endl;
	}
	m_bowSprite.setTexture(m_bowTexture);
	m_bowSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_bowSprite.setOrigin(m_bowSprite.getGlobalBounds().width / 2, m_bowSprite.getGlobalBounds().height / 2);
	m_bowSprite.setPosition(100, 100);
	m_bowSprite.setScale(2, 2);
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

void Bow::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
}

void Bow::animateBow()
{
	// draw animation

}

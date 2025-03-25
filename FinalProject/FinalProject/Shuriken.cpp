#include "Shuriken.h"

Shuriken::Shuriken()
{
	if (!shurikenTexture.loadFromFile("ASSETS/Weapons/SawBladeSuriken.png"))
	{
		std::cout << "Error loading shuriken texture" << std::endl;
	}
	m_shurikenSprite.setTexture(shurikenTexture);
	m_shurikenSprite.setTextureRect(sf::IntRect(0, 32, 30, 30));
	m_shurikenSprite.setOrigin(m_shurikenSprite.getGlobalBounds().width / 2, m_shurikenSprite.getGlobalBounds().height / 2);
	m_shurikenSprite.setPosition(10000, 10000);
	m_shurikenSprite.setScale(1, 1);

	//shuriken icon
	m_icon.setTexture(shurikenTexture);
	m_icon.setTextureRect(sf::IntRect(0, 32, 30, 30));
	m_icon.setScale(3, 3);
}

void Shuriken::render(sf::RenderWindow& window)
{
	window.draw(m_shurikenSprite);
}

void Shuriken::update(float deltaTime, sf::Vector2f playerPos)
{
}

void Shuriken::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	m_shurikenSprite.setPosition(playerPos);
}

sf::Sprite Shuriken::getSprite()
{
	return m_icon;
}

void Shuriken::animateShuriken()
{
}

void Shuriken::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
}

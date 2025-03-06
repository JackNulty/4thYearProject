#include "Sword.h"

Sword::Sword()
{
	if(!swordAttackTexture.loadFromFile("Assets/Weapons/Iron_Sword.png"))
	{
		std::cout << "Error loading sword texture" << std::endl;
	}
	if(!iconsTexture.loadFromFile("Assets/Weapons/Tool_Icons_NO_Outline.png"))
	{
		std::cout << "Error loading icons texture" << std::endl;
	}
	//icon
	m_swordIcon.setTexture(iconsTexture);
	m_swordIcon.setTextureRect(sf::IntRect(65, 0, 14, 14));
	m_swordIcon.setScale(5, 5);
	m_swordIcon.setOrigin(m_swordIcon.getGlobalBounds().width / 2, m_swordIcon.getGlobalBounds().height / 2);

	//sword animation frames

	//sword 
	m_swordSprite.setTexture(iconsTexture);
	m_swordSprite.setTextureRect(sf::IntRect(65, 0, 14, 14));
	m_swordSprite.setOrigin(m_swordSprite.getGlobalBounds().width / 2, m_swordSprite.getGlobalBounds().height / 2);
	m_swordSprite.setPosition(10000, 10000);
	m_swordSprite.setScale(2, 2);

}

void Sword::update(float deltaTime, sf::Vector2f playerPos)
{
	if (isActive)
	{
		m_swordSprite.setPosition(playerPos);
	}
	else if (!isActive)
	{
		m_swordSprite.setPosition(-1000000, -100);
	}
}

void Sword::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAnimating)
	{
		isAnimating = true;
		currentFrame = 0;
		frameCounter = 0;
	}
	if (isAnimating)
	{
		swordAnimation();
	}
	rotateAroundPlayer(playerPos, mousePos);
}

void Sword::render(sf::RenderWindow& window)
{
	window.draw(m_swordSprite);
	window.draw(m_swordIcon);
}

void Sword::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
}

sf::Sprite Sword::getSprite()
{
	return m_swordSprite;
}

void Sword::swordAnimation()
{
}

void Sword::rotateAroundPlayer(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	sf::Vector2f direction = mousePos - playerPos;
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	float angle = std::atan2(direction.y, direction.x) * 180 / PI;
	m_swordSprite.setRotation(angle);
}

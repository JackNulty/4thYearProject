#include "Boomerang.h"

Boomerang::Boomerang()
{
	if (!boomerangTexture.loadFromFile("ASSETS/Weapons/Boomerangs1.png"))
	{
		std::cout << "Error loading boomerang texture" << std::endl;
	}
	m_boomerangSprite.setTexture(boomerangTexture);
	m_boomerangSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_boomerangSprite.setOrigin(m_boomerangSprite.getGlobalBounds().width / 2, m_boomerangSprite.getGlobalBounds().height / 2);
	m_boomerangSprite.setPosition(10000, 10000);
	//boomerang icon
	m_icon.setTexture(boomerangTexture);
	m_icon.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_icon.setScale(0.5, 0.5);
}

void Boomerang::render(sf::RenderWindow& window)
{
	if (isFlying)
	{
		window.draw(m_boomerangSprite);
	}
}

void Boomerang::update(float deltaTime, sf::Vector2f playerPos)
{
	if (!isFlying) {
		m_boomerangSprite.setPosition(-10000, -10000);
	}
}

void Boomerang::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isFlying && !boomerangThrowFlag)
	{
		boomerangThrowFlag = true;
	}
	if (boomerangThrowFlag && !isFlying)
	{
		fire(playerPos, mousePos);
	}
	if (!isFlying)
	{
		return;
	}

	float move = speed * deltaTime;
	distanceTraveled += move;
	if (!isReturning)
	{
		position += direction * move;
		if (distanceTraveled >= maxDistance)
		{
			isReturning = true;
		}
	}
	else {
		sf::Vector2f returnDirection = playerPos - position;
		float returnMagnitude = std::sqrt(returnDirection.x * returnDirection.x + returnDirection.y * returnDirection.y);
		if (returnMagnitude != 0)
		{
			returnDirection /= returnMagnitude;
		}
		position += returnDirection * move;
		if (returnMagnitude < 10.0f)
		{
			reset();
		}
	}

	m_boomerangSprite.setPosition(position);
	m_boomerangSprite.rotate(rotationSpeed * deltaTime);
}

void Boomerang::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	if (!isActive || isFlying)
	{
		return;
	}

	direction = mousePos - playerPos;
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	position = playerPos;
	m_boomerangSprite.setPosition(position);
	distanceTraveled = 0.0f;
	isFlying = true;
	isReturning = false;
}

sf::Sprite Boomerang::getSprite()
{
	return m_icon;
}

#include "Dynamite.h"

Dynamite::Dynamite()
{
	if (!dynamiteTexture.loadFromFile("ASSETS/Weapons/dynamite.png"))
	{
		std::cout << "Error loading dynamite texture" << std::endl;
	}
	m_dynamiteSprite.setTexture(dynamiteTexture);
	m_dynamiteSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_dynamiteSprite.setOrigin(m_dynamiteSprite.getGlobalBounds().width / 2, m_dynamiteSprite.getGlobalBounds().height / 2);
	m_dynamiteSprite.setPosition(10000, 10000);

	m_explosionCircle.setFillColor(sf::Color(255, 100, 0, 100));

	m_dynamiteIcon.setTexture(dynamiteTexture);
	m_dynamiteIcon.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_dynamiteIcon.setScale(0.8, 0.8);
}

void Dynamite::update(float deltaTime, sf::Vector2f playerPos)
{
}

void Dynamite::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	if (isActive && state == Thrown)
	{
		velocity.y += gravity * deltaTime;
		m_dynamiteSprite.move(velocity * deltaTime);

		explosionTimer += deltaTime;
		if (explosionTimer >= timeBeforeExplode)
		{
			state = Exploding;
			explosionRadius = 0.f;
			showExplosion = true;
		}
	}
	else if (state == Exploding)
	{
		if (explosionRadius < maxExplosionRadius)
		{
			explosionRadius += 300.f * deltaTime; // expand quickly
			m_explosionCircle.setRadius(explosionRadius);
			m_explosionCircle.setOrigin(explosionRadius, explosionRadius);
			m_explosionCircle.setPosition(m_dynamiteSprite.getPosition());
		}
		else
		{
			reset();
		}
	}
}

void Dynamite::render(sf::RenderWindow& window)
{
	if (isActive && (state == Thrown || state == Exploding))
	{
		if (state == Thrown)
		{
			window.draw(m_dynamiteSprite);
		}
		if (showExplosion)
		{
			window.draw(m_explosionCircle);
		}
	}
}

void Dynamite::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	if (!isActive)
		return;

	m_dynamiteSprite.setPosition(playerPos);

	sf::Vector2f direction = mousePos - playerPos;
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}

	velocity = direction * 400.f; 
	velocity.y -= 200.f; 

	state = Thrown;
	explosionTimer = 0.0f;
}

sf::Sprite Dynamite::getSprite()
{
	return m_dynamiteIcon;
}

void Dynamite::reset()
{
	isActive = false;
	showExplosion = false;
	explosionTimer = 0.f;
	explosionRadius = 0.f;
	m_dynamiteSprite.setPosition(-10000, -10000);
	state = Idle;
}

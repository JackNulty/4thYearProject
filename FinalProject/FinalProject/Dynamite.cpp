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
	if (isActive) 
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !hasExploded)
		{
			fire(playerPos, mousePos);
		}
		if (explosionTimer < timeBeforeExplode)
		{
			explosionTimer += deltaTime;

			float throwProgress = explosionTimer / timeBeforeExplode;
			float throwDecay = 1 - throwProgress;
			m_dynamiteSprite.move(velocity * throwDecay * deltaTime);
			
			if (explosionTimer >= timeBeforeExplode)
			{
				hasExploded = true;
				showExplosion = true;
				explosionRadius = 0;

				ParticleManager& particleManager = ResourceManager::getParticleManager();
				std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
					"dynamite_explosion", 250, m_dynamiteSprite.getPosition());
				system->configure(200.f, 0.8f, 2.f, sf::Color::Red);
				std::cout << "Added new particle system: dynamite_explosion\n";
			}
		}
		else if (showExplosion)
		{
			explosionRadius += 200 * deltaTime;
			m_explosionCircle.setRadius(explosionRadius);
			m_explosionCircle.setPosition(m_dynamiteSprite.getPosition().x - explosionRadius, m_dynamiteSprite.getPosition().y - explosionRadius);
			if (explosionRadius >= maxExplosionRadius)
			{
				reset();
			}
		}
	}
}

void Dynamite::render(sf::RenderWindow& window)
{
	if (!isActive)
	{
		return;
	}
	if (showExplosion)
	{
		window.draw(m_explosionCircle);
	}
	else if (!hasExploded)
	{
		window.draw(m_dynamiteSprite);
	}
}

void Dynamite::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	if (!isActive)
	{
		return;
	}
	m_dynamiteSprite.setPosition(playerPos);
	m_dynamiteSprite.setRotation(atan2(mousePos.y - playerPos.y, mousePos.x - playerPos.x) * 180 / 3.14);

	sf::Vector2f direction = mousePos - playerPos;
	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction /= length;
	}
	velocity = direction * 300.f;

	explosionTimer = 0;
	
}

sf::Sprite Dynamite::getSprite()
{
	return m_dynamiteIcon;
}

void Dynamite::reset()
{
	isActive = false;
	m_dynamiteSprite.setPosition(10000, 10000);
	showExplosion = false;
	hasExploded = false;
	explosionRadius = 0;
	explosionTimer = 0;
}

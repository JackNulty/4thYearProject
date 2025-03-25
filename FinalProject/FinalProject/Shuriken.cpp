#include "Shuriken.h"

Shuriken::Shuriken()
{
	if (!shurikenTexture.loadFromFile("ASSETS/Weapons/SawBladeSuriken.png"))
	{
		std::cout << "Error loading shuriken texture" << std::endl;
	}
	m_shurikenSprite.setTexture(shurikenTexture);
	m_shurikenSprite.setTextureRect(sf::IntRect(6, 38, 20, 20));
	m_shurikenSprite.setOrigin(m_shurikenSprite.getGlobalBounds().width / 2, m_shurikenSprite.getGlobalBounds().height / 2);
	m_shurikenSprite.setPosition(10000, 10000);
	m_shurikenSprite.setScale(2, 2);

	//shuriken icon
	m_icon.setTexture(shurikenTexture);
	m_icon.setTextureRect(sf::IntRect(0, 32, 30, 30));
	m_icon.setScale(3, 3);

	//fill both animation frames
	m_shurikenFrames.push_back(sf::IntRect(6, 38, 20, 20));
	m_shurikenFrames.push_back(sf::IntRect(31, 39, 20, 20));
}

void Shuriken::render(sf::RenderWindow& window)
{
	if (shootShurikenFlag)
	{
		window.draw(m_shurikenSprite);
	}
}

void Shuriken::update(float deltaTime, sf::Vector2f playerPos)
{
	animateShuriken();
}

void Shuriken::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !shootShurikenFlag)
	{
		fire(playerPos, mousePos);
	}
	if (shootShurikenFlag)
	{
		m_shurikenSprite.move(velocity * deltaTime);
		if (checkBounds(cameraView))
		{
			reset();
		}
	}
	else {
		m_shurikenSprite.setPosition(playerPos);
	}
}

sf::Sprite Shuriken::getSprite()
{
	return m_icon;
}

void Shuriken::animateShuriken()
{
	if (shootShurikenFlag)
	{
		frameCounter++;
		if (frameCounter >= frameDelay)
		{
			frameCounter = 0;
			currentFrame++;
			if (currentFrame >= m_shurikenFrames.size())
			{
				currentFrame = 0;
			}
			m_shurikenSprite.setTextureRect(m_shurikenFrames[currentFrame]);
		}
	}
}

bool Shuriken::checkBounds(const sf::View& cameraView)
{
	sf::Vector2f currentPos = m_shurikenSprite.getPosition();
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

void Shuriken::fire(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	shootShurikenFlag = true;
	m_shurikenSprite.setPosition(playerPos);

	sf::Vector2f direction = mousePos - playerPos;
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction /= length;
	}

	velocity = direction * 500.0f;
}

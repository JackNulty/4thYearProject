#include "Bow.h"

Bow::Bow()
{
	if(!bowTexture.loadFromFile("Assets/Weapons/Bow_Stages.png"))
	{
		std::cout << "Error loading bow texture" << std::endl;
	}
	m_bowSprite.setTexture(bowTexture);
	m_bowSprite.setTextureRect(sf::IntRect(10, 0, 6, 16));
	m_bowSprite.setOrigin(m_bowSprite.getGlobalBounds().width / 2, m_bowSprite.getGlobalBounds().height / 2);
	m_bowSprite.setPosition(100, 100);
	m_bowSprite.setScale(2, 2);

	//bow animation frames
	m_bowFrames.push_back(sf::IntRect(10, 0, 6, 16));
	m_bowFrames.push_back(sf::IntRect(17, 0, 12, 16));
	m_bowFrames.push_back(sf::IntRect(30, 0, 11, 16));

	//arrow sprite
	m_arrowSprite.setTexture(bowTexture);
	m_arrowSprite.setTextureRect(sf::IntRect(60, 3, 4, 13));
	m_arrowSprite.setOrigin(m_arrowSprite.getGlobalBounds().width / 2, m_arrowSprite.getGlobalBounds().height / 2);
	m_arrowSprite.setScale(2, 2);
	m_arrowSprite.setPosition(600, 300);
}

void Bow::render(sf::RenderWindow& window)
{
	window.draw(m_bowSprite);
	window.draw(m_arrowSprite);
	for (auto arrow : m_arrowVector)
	{
		arrow.render(window);
	}
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
		m_arrowSprite.setPosition(playerPos);
	}
	else if (!isActive)
	{
		m_bowSprite.setPosition(-1000000, -100);
	}
}

void Bow::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isAnimating)
	{
		isAnimating = true;
		currentFrame = 0;
		frameCounter = 0;
		shootArrowFlag = true;
	}
	if (isAnimating)
	{
		animateBow();
	}

	rotateAroundPlayer(playerPos, mousePos);
	if (!isAnimating && shootArrowFlag)
	{
		shootArrow(playerPos, mousePos);
		shootArrowFlag = false;
	}

	for (auto arrow = m_arrowVector.begin(); arrow != m_arrowVector.end();)
	{
		arrow->fixedUpdate(deltaTime);
		if (arrow->checkBounds(cameraView))
		{
			arrow = m_arrowVector.erase(arrow);
		}
		else {
			++arrow;
		}
	}
}

std::vector<Arrow>& Bow::getArrows()
{
	return m_arrowVector;
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
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	float angle = std::atan2(direction.y, direction.x) * 180 / PI;
	m_bowSprite.setRotation(angle);
	m_arrowSprite.setRotation(angle + 270);
}

void Bow::shootArrow(sf::Vector2f playerPos, sf::Vector2f mousePos)
{
	sf::Vector2f direction = mousePos - playerPos;
	float magnitude = getMagnitude(direction);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	if (m_arrowVector.size() < MAX_ARROWS)
	{
		m_arrowVector.emplace_back(playerPos, arrowSpeed, direction, m_arrowSprite.getRotation());
	}
	else
	{
		m_arrowVector.erase(m_arrowVector.begin());
		m_arrowVector.emplace_back(playerPos, arrowSpeed, direction, m_arrowSprite.getRotation());
	}
}

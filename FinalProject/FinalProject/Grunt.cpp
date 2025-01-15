#include "Grunt.h"
#include "Bullet.h"

Grunt::Grunt(EnemyBehaviourTypes startBehaviour, float x, float y)
	: m_currentBehaviour(startBehaviour){
	m_gruntTexture = new sf::Texture();
	m_gruntTexture->loadFromFile("ASSETS/Enemies/Skeleton.png");
	m_gruntSprite.setTexture(*m_gruntTexture);
	m_gruntSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_gruntSprite.setOrigin(m_gruntSprite.getGlobalBounds().width / 2, m_gruntSprite.getGlobalBounds().height / 2);
	m_gruntSprite.setPosition(x, y);
	m_gruntSprite.setScale(2, 2);
	m_speed = 2;
}

void Grunt::update(float deltaTime)
{
}

void Grunt::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (m_currentBehaviour == EnemyBehaviourTypes::Seek)
	{
		sf::Vector2f steering = m_behaviours.calculateSeek(m_gruntSprite.getPosition(), playerPos, m_velocity, maxSpeed);
		m_acceleration += steering;
	}
	if (m_currentBehaviour == EnemyBehaviourTypes::Arrive)
	{
		sf::Vector2f steeringArrive = m_behaviours.calculateArrive(m_gruntSprite.getPosition(), playerPos, m_velocity, maxSpeed, 5.0f, 250.0f);
		m_acceleration += steeringArrive;
	}

	// limit velocity to max speed
	m_velocity += m_acceleration;
	float velocityMagnitude = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
	if (velocityMagnitude > maxSpeed)
	{
		m_velocity = (m_velocity / velocityMagnitude) * maxSpeed;
	}

	//update sprite
	m_gruntSprite.move(m_velocity);
	//m_gruntSprite.setRotation(m_behaviours.calculateRotation(m_gruntSprite.getPosition(), playerPos));
	gruntAnimations();

	// reset acceleration
	m_acceleration = { 0.0f, 0.0f };
}

void Grunt::render(sf::RenderWindow& window)
{
	window.draw(m_gruntSprite);
}

sf::FloatRect Grunt::getBounds() const
{
	return m_gruntSprite.getGlobalBounds();
}

sf::Vector2f Grunt::getPos() const
{
	return m_gruntSprite.getPosition();
}

void Grunt::setPos(sf::Vector2f pos)
{
	m_gruntSprite.setPosition(pos);
}

void Grunt::gruntAnimations()
{
	frameCounter++;
	if (frameCounter >= frameDelay)
	{
		frameCounter = 0;
		currentFrame++;
		if (currentFrame >= 6)
		{
			currentFrame = 0;
		}
		m_gruntSprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 96, frameWidth, frameHeight));
	}
}


#include "Grunt.h"
#include "Bullet.h"

Grunt::Grunt(EnemyBehaviourTypes startBehaviour, float x, float y)
	: m_currentBehaviour(startBehaviour){
	m_gruntShape.setSize(sf::Vector2f(30, 30));
	m_gruntShape.setOrigin(m_gruntShape.getSize().x / 2, m_gruntShape.getSize().y / 2);
	m_gruntShape.setFillColor(sf::Color::Red);
	m_gruntShape.setPosition(x, y);
	m_speed = 2;
}

void Grunt::update(float deltaTime)
{
}

void Grunt::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (m_currentBehaviour == EnemyBehaviourTypes::Seek)
	{
		sf::Vector2f steering = m_behaviours.calculateSeek(m_gruntShape.getPosition(), playerPos, m_velocity, maxSpeed);
		m_acceleration += steering;
	}

	// limit velocity to max speed
	m_velocity += m_acceleration;
	float velocityMagnitude = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
	if (velocityMagnitude > maxSpeed)
	{
		m_velocity = (m_velocity / velocityMagnitude) * maxSpeed;
	}

	//update sprite
	m_gruntShape.move(m_velocity);
	m_gruntShape.setRotation(m_behaviours.calculateRotation(m_gruntShape.getPosition(), playerPos));

	// reset acceleration
	m_acceleration = { 0.0f, 0.0f };
}

void Grunt::render(sf::RenderWindow& window)
{
	window.draw(m_gruntShape);
}

sf::FloatRect Grunt::getBounds() const
{
	return m_gruntShape.getGlobalBounds();
}


#include "Heavy.h"

Heavy::Heavy(EnemyBehaviourTypes startBehaviour, float x, float y)
	: m_currentBehaviour(startBehaviour)
{
	m_heavyShape.setSize(sf::Vector2f(40, 40));
	m_heavyShape.setOrigin(m_heavyShape.getSize().x, m_heavyShape.getSize().y);
	m_heavyShape.setFillColor(sf::Color::Blue);
	m_heavyShape.setPosition(x, y);
	m_speed = 1.5f;
}

void Heavy::update(float deltaTime)
{
}

void Heavy::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (m_currentBehaviour == EnemyBehaviourTypes::Seek)
	{
		sf::Vector2f steering = m_behaviours.calculateSeek(m_heavyShape.getPosition(), playerPos, m_velocity, maxSpeed);
		m_acceleration += steering;
	}
	if (m_currentBehaviour == EnemyBehaviourTypes::Arrive)
	{
		sf::Vector2f steeringArrive = m_behaviours.calculateArrive(m_heavyShape.getPosition(), playerPos, m_velocity, maxSpeed, 5.0f, 250.0f);
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
	m_heavyShape.move(m_velocity);
	m_heavyShape.setRotation(m_behaviours.calculateRotation(m_heavyShape.getPosition(), playerPos));

	// reset acceleration
	m_acceleration = { 0.0f, 0.0f };
}

void Heavy::render(sf::RenderWindow& window)
{
	window.draw(m_heavyShape);
}

sf::FloatRect Heavy::getBounds() const
{
	return m_heavyShape.getGlobalBounds();
}

sf::Vector2f Heavy::getPos() const
{
	return m_heavyShape.getPosition();
}

void Heavy::setPos(sf::Vector2f pos)
{
	m_heavyShape.setPosition(pos);
}

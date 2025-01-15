#pragma once
#include "globals.h"

class EnemyBehaviours {
public:
	sf::Vector2f calculateSeek(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, const sf::Vector2f& currentVelocity, float speed);
	sf::Vector2f calculateArrive(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, const sf::Vector2f& currentVelocity, float maxSpeed, float arrivalRadius, float slowRadius);
	float calculateRotation(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition);

private:
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float maxSpeed = 5.0f;
	float maxForce = 0.1f;
};

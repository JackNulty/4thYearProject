#pragma once
#include "globals.h"

class EnemyBehaviours {
public:
	sf::Vector2f calculateSeek(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, const sf::Vector2f& currentVelocity, float speed);
	float calculateRotation(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition);

private:
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float maxSpeed = 5.0f;
	float maxForce = 0.1f;
};

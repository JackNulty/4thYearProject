#pragma once
#include "globals.h"

class EnemyBehaviours {
public:
	sf::Vector2f calculateSeek(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition, float speed);
	float calculateRotation(const sf::Vector2f& currentPosition, const sf::Vector2f& targetPosition);
};

#pragma once
#include "globals.h"

class Bullet
{
public:
	Bullet(sf::Vector2f playerPos, sf::Vector2f direction, float speed);
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	bool checkBounds();
	sf::FloatRect getBounds() const;

private:
	sf::CircleShape bulletShape;
	sf::Vector2f direction;
	float speed;
};


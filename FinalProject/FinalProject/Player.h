#pragma once
#include "globals.h"

class Player
{
public:
	Player();
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	void render(sf::RenderWindow& window);

private:

	//private functions
	void playerMovement(float deltaTime);

	//private vars
	sf::RectangleShape playerShape;
	float speed = 100.0f;
};


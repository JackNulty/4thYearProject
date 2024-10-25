#pragma once
#include "globals.h"

class Level
{
public:
	Level();
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	void render(sf::RenderWindow& window);

private:

};

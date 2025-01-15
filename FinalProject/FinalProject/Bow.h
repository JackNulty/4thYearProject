#pragma once
#include "globals.h"

class Bow
{
public:
	Bow();
	void render(sf::RenderWindow& window);
	void update(float deltaTime, sf::Vector2f playerPos);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);

private:

	//private functions
	void animateBow();

	//private vars
	sf::Texture m_bowTexture;
	sf::Sprite m_bowSprite;
	bool isActive = false;

};

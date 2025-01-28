#pragma once
#include "globals.h"

class Arrow
{
public:
	Arrow(sf::Texture *arrowTexture, sf::Vector2f playerPos, float speed, sf::Vector2f direction, float rotation);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime);
	void render(sf::RenderWindow& window);
	bool checkBounds();
	sf::FloatRect getBounds() const;

private:
	sf::Sprite m_arrowSprite;
	sf::Vector2f m_direction;
	float m_speed;

};

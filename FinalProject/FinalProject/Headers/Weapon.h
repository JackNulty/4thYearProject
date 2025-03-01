#pragma once
#include "globals.h"

class Weapon {
public:
	Weapon();
	virtual ~Weapon() = default;
	virtual void update(float deltaTime, sf::Vector2f playerPos) = 0;
	virtual void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView)= 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) = 0;
	virtual sf::Sprite getSprite() = 0;

private:
	sf::Sprite m_sprite;
};

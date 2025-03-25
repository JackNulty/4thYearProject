#pragma once
#include "globals.h"
#include "Weapon.h"

class Shuriken : public Weapon
{
public:
	Shuriken();
	void render(sf::RenderWindow& window) override;
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;

	sf::Sprite getSprite() override;
	void setActive(bool active) override { isActive = active; }

private:
	void animateShuriken();
	void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;

	sf::Sprite m_shurikenSprite;
	sf::Sprite m_icon;
	bool isAnimating = false;
	const int frameDelay = 25; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
};

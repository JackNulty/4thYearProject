#pragma once
#include "globals.h"
#include "Weapon.h"

class Boomerang : public Weapon
{
public:
	Boomerang();
	void render(sf::RenderWindow& window) override;
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;
	void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;
	sf::Sprite getSprite() override;
	void setActive(bool active) override { isActive = active; }
	bool getAttackFlag() { return boomerangThrowFlag; }
	sf::FloatRect getBounds() { return m_boomerangSprite.getGlobalBounds(); }
	void reset() { boomerangThrowFlag = false; isFlying = false; isReturning = false; distanceTraveled = 0.0f; m_boomerangSprite.setPosition(10000, 10000); }

private:
	sf::Sprite m_boomerangSprite;
	sf::Sprite m_icon;

	sf::Vector2f direction;
	sf::Vector2f position;
	float speed = 800.0f;
	float rotationSpeed = 400.0f;
	float maxDistance = 300.0f;
	float distanceTraveled = 0.0f;
	bool isFlying = false;
	bool isReturning = false;
	bool boomerangThrowFlag = false;


};
#pragma once
#include "globals.h"
#include "Enemy.h"

class Archer : public Enemy {
public:
	Archer(float x, float y);
	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos) override;
	void attack() override;

private:
	void archerAnimations();
	int frameDelay = 315;
	int frameCounter = 0;
	int currentFrame = 0;
	int frameWidth = 32;
	int frameHeight = 32;

}

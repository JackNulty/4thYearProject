#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"
#include "Enemy.h"

class Archer : public Enemy {
public:
	Archer(float x, float y);
	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos) override;
	void attack() override;

private:
	void archerAnimations();
	void fillFrames();
	int frameDelay = 215;
	int frameCounter = 0;
	int currentFrame = 0;
	int frameWidth = 16;
	int frameHeight = 23;

	std::vector<sf::Vector2f> m_moveFrames;
	int m_currentMoveFrame = 0;

};

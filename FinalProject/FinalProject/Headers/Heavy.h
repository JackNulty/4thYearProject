#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"
#include "Enemy.h"

class Heavy : public Enemy
{
public:
	Heavy(float x, float y);
	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos) override;

private:

    void heavyAnimations();
    int frameDelay = 315;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;
};


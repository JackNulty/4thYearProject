#pragma once
#include "globals.h"
#include "Enemy.h"

class Grunt : public Enemy {
public:
    Grunt(float x, float y);
    void update(float deltaTime) override;
    void fixedUpdate(float deltaTime, sf::Vector2f playerPos) override;

private:
    void gruntAnimations();
    int frameDelay = 315;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;
};


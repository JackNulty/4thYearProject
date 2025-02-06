#pragma once
#include "globals.h"

class Enemy;

class Behaviour {
public:
    virtual void update(Enemy& enemy, const sf::Vector2f& playerPos) = 0;
    virtual ~Behaviour() = default;
};
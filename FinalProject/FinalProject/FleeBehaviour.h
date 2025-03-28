#pragma once
#include "globals.h"
#include "Behaviour.h"
#include "Enemy.h"

class FleeBehaviour : public Behaviour {
public:
	void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
};


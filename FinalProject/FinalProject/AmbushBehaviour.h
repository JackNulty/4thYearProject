#pragma once
#include "globals.h"
#include "Behaviour.h"
#include "Enemy.h"

class AmbushBehaviour : public Behaviour {
public:
	void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
	std::unique_ptr<Behaviour> clone() const override;
};

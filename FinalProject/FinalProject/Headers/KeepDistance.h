#pragma once
#include "globals.h"
#include "Behaviour.h"


class KeepDistance : public Behaviour {
public:
	void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
};


#pragma once
#include "globals.h"

class PlayerHitEffect
{
public:
	PlayerHitEffect(sf::Texture& texture, sf::Vector2f position);
	void update();
	bool isFinished() const;
	sf::Sprite sprite;

private:
	sf::Clock clock;
	float duration = 0.5f;
};


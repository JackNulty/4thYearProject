#pragma once
#include "globals.h"
#include "Weapon.h"

class Shuriken : public Weapon
{
public:
	Shuriken();
	void render(sf::RenderWindow& window) override;
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;

	void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;

	sf::Sprite getSprite() override;
	void setActive(bool active) override { isActive = active; }
	bool getAttackFlag() { return shootShurikenFlag; }
	sf::FloatRect getBounds() { return m_shurikenSprite.getGlobalBounds(); }
	void reset() { shootShurikenFlag = false; }

private:
	void animateShuriken();
	bool checkBounds(const sf::View& cameraView);

	sf::Sprite m_shurikenSprite;
	sf::Sprite m_icon;
	bool isAnimating = false;
	bool shootShurikenFlag = false;
	const int frameDelay = 5; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation

	std::vector<sf::IntRect> m_shurikenFrames;

	sf::Vector2f velocity;
};

#pragma once
#include "globals.h"
#include "Weapon.h"


class Sword : public Weapon {
public:
	Sword();
	~Sword() = default;
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;
	void render(sf::RenderWindow& window) override;
	void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;
	sf::Sprite getSprite() override;
	void setActive(bool active) override { isActive = active; }

private:
	void swordAnimation();
	void rotateAroundPlayer(sf::Vector2f playerPos, sf::Vector2f mousePos);

	sf::Sprite m_swordSprite;
	bool isAnimating = false;
	const int frameDelay = 25; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
	std::vector<sf::IntRect> m_swordFrames;

	sf::Sprite m_swordIcon;
};

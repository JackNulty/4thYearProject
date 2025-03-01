#pragma once
#include "globals.h"
#include "Arrow.h"
#include "Weapon.h"


class Bow : public Weapon
{
public:
	Bow();
	void render(sf::RenderWindow& window) override;
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;
	std::vector<Arrow>& getArrows();
	sf::Sprite getSprite() override;

private:

	//private functions
	void animateBow();
	void rotateAroundPlayer(sf::Vector2f playerPos, sf::Vector2f mousePos);
	void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;

	//private vars
	sf::Sprite m_bowSprite;
	sf::Sprite m_arrowSprite;
	bool isActive = false;
	bool isAnimating = false;
	const int frameDelay = 25; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
	std::vector<sf::IntRect> m_bowFrames;

	//arrow vars
	std::vector<Arrow> m_arrowVector;
	const int MAX_ARROWS = 20;
	int m_arrowDelay = 0;
	const int maxArrowDelay = 10;
	const int arrowSpeed = 1000;
	const int arrowRotation = 0;
	bool shootArrowFlag = false;

	//bow picture
	sf::Sprite m_bowIcon;

};

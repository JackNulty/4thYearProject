#pragma once
#include "globals.h"

class Bow
{
public:
	Bow();
	void render(sf::RenderWindow& window);
	void update(float deltaTime, sf::Vector2f playerPos);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos);

private:

	//private functions
	void animateBow();
	void rotateAroundPlayer(sf::Vector2f playerPos, sf::Vector2f mousePos);

	//private vars
	sf::Texture m_bowTexture;
	sf::Sprite m_bowSprite;
	sf::Sprite m_arrowSprite;
	bool isActive = false;
	bool isAnimating = false;
	const int frameDelay = 25; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
	std::vector<sf::IntRect> m_bowFrames;

};

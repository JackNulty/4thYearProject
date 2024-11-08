#pragma once
#include "globals.h"
#include "Bullet.h"

class Player
{
public:
	Player();
	void update(float deltaTime, sf::Vector2f mousePos);
	void fixedUpdate(float deltaTime, sf::Vector2f mousePos);
	void render(sf::RenderWindow& window);
	sf::Vector2f getPos(); //  get player position
	std::vector<Bullet>& getBullets(); // get container of bullets

private:

	//private functions
	void playerMovement(float deltaTime); // func for player movement
	void shootBullet(sf::Vector2f mousePos); // func for shooting bullet 

	//private vars
	sf::RectangleShape playerShape; // shape of player (placeholder for texture)
	float speed = 100.0f; // player speed
	std::vector<Bullet> bulletVector; // container for bullets
	const int MAX_BULLETS = 20; // maxz number of bullets
	int bulletDelay = 0; // delay counter for bullets
	const int maxBulletDelay = 10; // max delay for each mouse click to shoot bullets
};


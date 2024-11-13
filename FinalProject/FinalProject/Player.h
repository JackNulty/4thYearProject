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
	sf::RectangleShape m_playerShape; // shape of player (placeholder for texture)
	float m_speed = 300.0f; // player speed
	std::vector<Bullet> m_bulletVector; // container for bullets
	const int MAX_BULLETS = 20; // maxz number of bullets
	int m_bulletDelay = 0; // delay counter for bullets
	const int maxBulletDelay = 10; // max delay for each mouse click to shoot bullets
};


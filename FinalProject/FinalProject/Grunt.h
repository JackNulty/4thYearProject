#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"

class Grunt
{
public:
	Grunt(EnemyBehaviourTypes startBehaviour);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const; 

private:
	//private functions

	//private vars
	sf::RectangleShape gruntShape;
	EnemyBehaviours behaviours;
	EnemyBehaviourTypes currentBehaviour;
	float m_speed;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float maxSpeed = 5.0f;
	float maxForce = 0.1f;

};


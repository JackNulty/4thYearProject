#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"

class Grunt
{
public:
	Grunt(EnemyBehaviourTypes startBehaviour, float x, float y);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const; 

private:
	//private functions

	//private vars
	sf::RectangleShape m_gruntShape;
	EnemyBehaviours m_behaviours;
	EnemyBehaviourTypes m_currentBehaviour;
	float m_speed;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float maxSpeed = 5.0f;
	float maxForce = 0.1f;

};


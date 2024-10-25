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

private:
	//private functions

	//private vars
	sf::RectangleShape gruntShape;
	EnemyBehaviours behaviours;
	EnemyBehaviourTypes currentBehaviour;
	int m_speed;

};


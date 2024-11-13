#pragma once
#include "globals.h"
#include "Grunt.h"


class Horde
{
public:
	Horde(int maxEnemies, EnemyBehaviourTypes setupBehaviour, sf::Vector2f centreHorde);
	std::vector<Grunt> m_grunts;
	sf::Clock m_formationClock;
	void generateFormation(int maxEnemies, EnemyBehaviourTypes setupBehaviour, sf::Vector2f centreHorde);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);

private:
	float radius = 100.0f;
};

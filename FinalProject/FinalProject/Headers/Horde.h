#pragma once
#include "globals.h"
#include "Grunt.h"
#include "Bullet.h"
#include "HordeFormationsEnum.h"
#include "SeekBehaviour.h"
#include "KeepDistance.h"
#include "Enemy.h"


class Horde
{
public:
	Horde(int maxEnemies, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing);
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	sf::Clock m_formationClock;
	std::vector<sf::Vector2f> generateFormation(int maxEnemies, sf::Vector2f centreHorde, int enemySpacing);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);
	HordeFormation m_currentFormation;
	void setFormation(HordeFormation type, sf::Vector2f centreHorde, int enemySpacing);

private:
	std::vector<sf::Vector2f> positions;
	void seperation();
	float radius = 100.0f;
};

#pragma once
#include "globals.h"
#include "Grunt.h"
#include "Bullet.h"
#include "HordeFormationsEnum.h"
#include "SeekBehaviour.h"
#include "KeepDistance.h"
#include "FollowLeaderBehaviour.h"
#include "Enemy.h"
#include "Archer.h"
#include "Heavy.h"


class Horde
{
public:
	Horde(int maxEnemies, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing);
	std::vector<std::shared_ptr<Enemy>> m_enemies;
	sf::Clock m_formationClock;
	std::vector<sf::Vector2f> generateFormation(int maxEnemies, sf::Vector2f centreHorde, int enemySpacing);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView);
	void render(sf::RenderWindow& window);
	HordeFormation m_currentFormation;
	void setFormation(HordeFormation type, sf::Vector2f centreHorde, int enemySpacing);
	void setLeader();
	std::weak_ptr<Enemy> getLeader() { return m_leader; }

private:
	std::vector<sf::Vector2f> positions;
	void seperation();
	std::vector<int> enemyTypes(int MAX_ENEMIES);
	float radius = 100.0f;
	std::weak_ptr<Enemy> m_leader;
	void assignLeader();
};

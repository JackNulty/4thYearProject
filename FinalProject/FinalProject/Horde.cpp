#include "Horde.h"

Horde::Horde(int maxEnemies, EnemyBehaviourTypes setupBehaviour, sf::Vector2f centreHorde)
{
	generateFormation(maxEnemies, setupBehaviour, centreHorde);
}

void Horde::generateFormation(int maxEnemies, EnemyBehaviourTypes setupBehaviour, sf::Vector2f centreHorde)
{
	// circle formation
	// for each enemy place aroud the circumferance of a circle
	float angleDivder = 360.0f / maxEnemies;
	for (int i = 0; i < maxEnemies; i++)
	{
		float angle = i * angleDivder;
		float x = centreHorde.x + radius * cos(angle * (PI / 180.0f));
		float y = centreHorde.y + radius * sin(angle * (PI / 180.0f));
		m_grunts.push_back(Grunt(setupBehaviour, x, y));
	}
}

void Horde::update(float deltaTime)
{
	if (m_formationClock.getElapsedTime().asSeconds() >= 5.0f)
	{
		for (auto& grunt : m_grunts)
		{
			grunt.update(deltaTime);
		}
	}
}

void Horde::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (m_formationClock.getElapsedTime().asSeconds() >= 5.0f)
	{
		for (auto& grunt : m_grunts)
		{
			grunt.fixedUpdate(deltaTime, playerPos);
		}
	}
}

void Horde::render(sf::RenderWindow& window)
{
	for (auto& grunt : m_grunts)
	{
		grunt.render(window);
	}
}

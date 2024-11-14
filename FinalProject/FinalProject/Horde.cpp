#include "Horde.h"

Horde::Horde(int maxEnemies, EnemyBehaviourTypes setupBehaviour, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing)
{
	m_currentFormation = startFormation;
	positions = generateFormation(maxEnemies, centreHorde, enemySpacing);
	for (const auto& position : positions)
	{
		m_grunts.emplace_back(Grunt(setupBehaviour, position.x, position.y));
	}
}

std::vector<sf::Vector2f> Horde::generateFormation(int maxEnemies, sf::Vector2f centreHorde, int enemySpacing)
{
	// vector for positions of enemy hordes
	std::vector<sf::Vector2f> positions;

	if (m_currentFormation == HordeFormation::Circle)
	{
		// circle formation
		// for each enemy place aroud the circumference of a circle
		radius = (maxEnemies * enemySpacing) / (2 * PI); // dynamically adjust radius of cirlce depending on the number of enemies and the spacing between them
		float angleDivder = 2 * PI / maxEnemies;
		for (int i = 0; i < maxEnemies; i++)
		{
			float angle = i * angleDivder;
			float x = centreHorde.x + std::cos(angle) * radius;
			float y = centreHorde.y + std::sin(angle) * radius;
			positions.emplace_back(x, y);
		}
	}
	if (m_currentFormation == HordeFormation::Grid)
	{
		// grid formation
		// place formation in a grid based on rows and columns
		int gridSize = static_cast<int>(std::sqrt(maxEnemies)); // calc for getting dimensions of grid
		for (int i = 0; i < maxEnemies; i++)
		{
			int row = i / gridSize;
			int col = i % gridSize;
			float x = centreHorde.x + (col - gridSize / 2) * enemySpacing;
			float y = centreHorde.y + (row - gridSize / 2) * enemySpacing;
			positions.emplace_back(x,y);
		}
	}
	if (m_currentFormation == HordeFormation::Cluster)
	{
		//cluster formation
		int clusterAmount = maxEnemies / 8;
		if (clusterAmount <= 1)
		{
			clusterAmount = 1;
		}
		int perCluster = maxEnemies / clusterAmount;
		float clusterRadius = enemySpacing;
		float clusterSpacing = enemySpacing * 2;
		for (int clusterCount = 0; clusterCount < clusterAmount; clusterCount++)
		{
			// get a centre per cluster near enough the main centre given
			float angle = (2 * PI / clusterAmount) * clusterCount;
			float x = centreHorde.x + std::cos(angle) * clusterRadius;
			float y = centreHorde.y + std::sin(angle) * clusterRadius;
			sf::Vector2f clusterCentre(x, y);
			for (int i = 0; i < perCluster; i++)
			{
				//then generate positions within each cluster
				float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2 * PI;
				float randomDistance = static_cast<float>(rand()) / RAND_MAX * clusterSpacing;
				float posX = clusterCentre.x + std::cos(randomAngle) * randomDistance;
				float posY = clusterCentre.y + std::sin(randomAngle) * randomDistance;
				positions.emplace_back(posX, posY);
			}
		}
	}

	return positions;

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
	seperation();
}

void Horde::render(sf::RenderWindow& window)
{
	for (auto& grunt : m_grunts)
	{
		grunt.render(window);
	}
}

void Horde::setFormation(HordeFormation type, sf::Vector2f centreHorde, int enemySpacing)
{
	m_currentFormation = type;
	positions = generateFormation(m_grunts.size(), centreHorde, enemySpacing);
	for (int i = 0; i < m_grunts.size(); i++)
	{
		m_grunts[i].setPos(positions[i]);
	}
}

void Horde::seperation()
{
	// loop through horde or grunts
	for (int i = 0; i < m_grunts.size(); i++)
	{
		sf::Vector2f seperationForce(0.0f, 0.0f);
		// loop through horde to check they are not colliding 
		for (int index = 0; index < m_grunts.size(); index++)
		{
			// if its not itself
			if (i != index)
			{
				// get the vector and distance between the currrent enemy and get the seperation force of them 
				sf::Vector2f vectorBetween = m_grunts[i].getPos() - m_grunts[index].getPos();
				float distanceBetween = std::sqrt(vectorBetween.x * vectorBetween.x + vectorBetween.y * vectorBetween.y);
				if (distanceBetween < 30.0f && distanceBetween > 0.0f)
				{
					seperationForce += vectorBetween / distanceBetween;
				}
			}
		}
		// normalise seperation force and multiply
		seperationForce = normalize(seperationForce) * 2.0f;
		// add seperation force to each enemies velocity
		m_grunts[i].m_velocity += seperationForce;
	}
}


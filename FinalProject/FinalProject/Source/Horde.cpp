#include "Horde.h"


Horde::Horde(int maxEnemies, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing)
{
	m_currentFormation = startFormation;
	positions = generateFormation(maxEnemies, centreHorde, enemySpacing);
    std::vector<int> types = enemyTypes(maxEnemies);
    for (size_t i = 0; i < positions.size(); ++i)
    {
		switch (types[i])
		{
			case 0:
				m_enemies.emplace_back(std::make_unique<Archer>(positions[i].x, positions[i].y));
			break;
			case 1:
				m_enemies.emplace_back(std::make_unique<Grunt>(positions[i].x, positions[i].y));
			break;
			case 2:
				m_enemies.emplace_back(std::make_unique<Heavy>(positions[i].x, positions[i].y));
			break;
			default:
				m_enemies.emplace_back(std::make_unique<Archer>(positions[i].x, positions[i].y));
			break;
		}
    }
	assignLeader();
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
		float clusterRadius = enemySpacing * 4;
		std::vector<sf::Vector2f> clusterPositions;
		for (int i = 0; i < maxEnemies; i++)
		{
			sf::Vector2f newEnemyPosition;
			bool validPosition = false;
			//keep looping unitl no overlap
			while (!validPosition) {
				//then generate positions around the centre
				float randomAngle = static_cast<float>(rand()) / RAND_MAX * 2 * PI;
				float randomDistance = static_cast<float>(rand()) / RAND_MAX * clusterRadius;
				float posX = centreHorde.x + std::cos(randomAngle) * randomDistance;
				float posY = centreHorde.y + std::sin(randomAngle) * randomDistance;
				newEnemyPosition = sf::Vector2f(posX, posY);
				// assume validity initially
				validPosition = true;
				// check against rest of cluster
				for (sf::Vector2f& existingPos : clusterPositions) {
					sf::Vector2f vectorBetween = newEnemyPosition - existingPos;
					float distanceBetween = std::sqrt(vectorBetween.x * vectorBetween.x + vectorBetween.y * vectorBetween.y);

					if (distanceBetween < enemySpacing) { // Minimum distance
						validPosition = false;
						break;
					}
				}
			}
			// Add the positions to the cluster and the global positions
			clusterPositions.emplace_back(newEnemyPosition);
			positions.emplace_back(newEnemyPosition);
		}
	}

	return positions;

}

void Horde::update(float deltaTime)
{
	if (m_formationClock.getElapsedTime().asSeconds() >= 5.0f)
	{
		for (auto& enemy : m_enemies)
		{
			enemy->update(deltaTime);
		}
	}
}

void Horde::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView)
{
	if (m_formationClock.getElapsedTime().asSeconds() >= 5.0f)
	{
		if (m_leader.expired()) {
			//std::cout << "Leader expired." << std::endl;
			return;
		}

        std::shared_ptr<Enemy> leader = m_leader.lock();

        float distanceToPlayer = std::sqrt(
        std::pow(leader->getPos().x - playerPos.x, 2) +
        std::pow(leader->getPos().y - playerPos.y, 2)
        );

        if (distanceToPlayer < 20.0f) {  // Formation trigger distance
			setFormation(HordeFormation::Circle, leader->getPos(), 40);
        }

		for (auto& enemy : m_enemies) {
			enemy->fixedUpdate(deltaTime,playerPos,cameraView);
			//std::cout << "Enemy position: " << enemy->getPos().x << ", " << enemy->getPos().y << std::endl;
		}
	}
	seperation();
}

void Horde::render(sf::RenderWindow& window)
{
	for (auto& enemy : m_enemies)
	{
		enemy->render(window);
	}
}

void Horde::setFormation(HordeFormation type, sf::Vector2f centreHorde, int enemySpacing)
{
	m_currentFormation = type;
	positions = generateFormation(m_enemies.size(), centreHorde, enemySpacing);
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->setPos(positions[i]);
	}
}

void Horde::setLeader()
{
	assignLeader();
}

void Horde::assignLeader()
{
	if (m_enemies.empty()) {
		m_leader.reset();
		return;
	}

	m_leader = m_enemies.front();
	//std::cout << "New leader assigned." << std::endl;

	for (auto& enemy : m_enemies) {
		if (enemy == m_leader.lock()) {
			enemy->setBehaviour(std::make_unique<SeekBehaviour>());
			//std::cout << "Leader behavior set to SeekBehaviour." << std::endl;
		}
		else {
			enemy->setBehaviour(std::make_unique<FollowLeaderBehaviour>(m_leader));
			//std::cout << "Follower behavior set to FollowLeaderBehaviour." << std::endl;
		}
	}
}

void Horde::seperation()
{
	// loop through horde or grunts
	for (int i = 0; i < m_enemies.size(); i++)
	{
		sf::Vector2f seperationForce(0.0f, 0.0f);
		// loop through horde to check they are not colliding 
		for (int index = 0; index < m_enemies.size(); index++)
		{
			// if its not itself
			if (i != index)
			{
				// get the vector and distance between the currrent enemy and get the seperation force of them 
				sf::Vector2f vectorBetween = m_enemies[i]->getPos() - m_enemies[index]->getPos();
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
		m_enemies[i]->m_velocity += seperationForce;
	}
}

std::vector<int> Horde::enemyTypes(int MAX_ENEMIES)
{
    std::vector<int> types;
    types.reserve(MAX_ENEMIES);
    for (int i = 0; i < MAX_ENEMIES; ++i)
    {
        int type = rand() % 3;
        types.push_back(type);
    }
    return types;
}


#include "Horde.h"


Horde::Horde(int maxEnemies, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing)
{
	m_currentFormation = startFormation;
	if (startFormation == HordeFormation::Circle)
	{
		m_circleFormation = true;
		m_circleState = CircleState::MovingToPositions;
		m_currentRadius = 300.0f;
		m_targetRadius = 50.0f;
	}
	if (startFormation == HordeFormation::Cluster)
	{
		m_converging = true;
		m_convergingState = ConvergingState::MovingToClusters;
	}
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
			case 3:
				m_enemies.emplace_back(std::make_unique<Thief>(positions[i].x, positions[i].y));
			break;
			default:
				m_enemies.emplace_back(std::make_unique<Archer>(positions[i].x, positions[i].y));
			break;
		}
		//m_enemies.emplace_back(std::make_unique<Thief>(positions[i].x, positions[i].y));
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

					if (distanceBetween < enemySpacing) { // Minimum distancew
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

void Horde::update(float deltaTime, sf::Vector2f playerPos)
{
	if (m_formationClock.getElapsedTime().asSeconds() >= 5.0f)
	{
		for (auto& enemy : m_enemies)
		{
			enemy->update(deltaTime, playerPos);
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
		for (auto& enemy : m_enemies) {
			enemy->fixedUpdate(deltaTime,playerPos,cameraView);
			//std::cout << "Enemy position: " << enemy->getPos().x << ", " << enemy->getPos().y << std::endl;
		}
	}
	seperation();
	if (m_circleFormation)
	{
		if (m_circleState == CircleState::MovingToPositions)
		{
			updateCircleFormation(playerPos, deltaTime);
			bool checkHordeInPlace = true;
			for (int i = 0; i < m_enemies.size(); i++)
			{
				float distance = std::sqrt(
					std::pow(m_enemies[i]->getPos().x - m_circleTargets[i].x, 2) +
					std::pow(m_enemies[i]->getPos().y - m_circleTargets[i].y, 2)
				);
				if (distance > 30.0f)
				{
					checkHordeInPlace = false;
				}
				auto* behaviour = dynamic_cast<CirclePointBehaviour*>(m_enemies[i]->getBehaviour());
				if (behaviour)
				{
					behaviour->setTarget(m_circleTargets[i]);
				}
				else {
					auto newBehaviour = std::make_unique<CirclePointBehaviour>(m_circleTargets[i]);
					newBehaviour->setTarget(m_circleTargets[i]);
					m_enemies[i]->setBehaviour(std::move(newBehaviour));
				}
			}
			if (checkHordeInPlace)
			{
				m_circleState = CircleState::ClosingIn;
			}
		}
		else if (m_circleState == CircleState::ClosingIn)
		{
			updateCircleFormation(playerPos, deltaTime);
			for (int i = 0; i < m_enemies.size(); i++)
			{
				auto* behaviour = dynamic_cast<CirclePointBehaviour*>(m_enemies[i]->getBehaviour());
				if (behaviour)
				{
					behaviour->setTarget(m_circleTargets[i]);
				}
			}
		}
	}
	if (m_converging)
	{
		if (m_convergingState == ConvergingState::MovingToClusters)
		{
			updateConvergingFormation(playerPos, deltaTime);
			bool checkHordeInPlace = true;

			for (int i = 0; i < m_enemies.size(); i++)
			{
				auto* behaviour = dynamic_cast<CirclePointBehaviour*>(m_enemies[i]->getBehaviour());
				if (!behaviour)
				{
					auto newBehaviour = std::make_unique<CirclePointBehaviour>(m_clusterTargets[i]);
					m_enemies[i]->setBehaviour(std::move(newBehaviour));
				}
				else {
					behaviour->setTarget(m_clusterTargets[i]);
				}

				// check dist
				sf::Vector2f vectorBetween = m_clusterTargets[i] - m_enemies[i]->getPos();
				float distanceBetween = std::sqrt(vectorBetween.x * vectorBetween.x + vectorBetween.y * vectorBetween.y);
				if (distanceBetween > 80.0f)
				{
					checkHordeInPlace = false;
				}
			}
			if (checkHordeInPlace)
			{
				std::cout << "Horde in place" << std::endl;
				m_convergingState = ConvergingState::Engaging;
				m_clusterTargets.clear();
				for (auto& enemy : m_enemies)
				{
					sf::Vector2f target = playerPos - enemy->getPos();
					float distance = std::sqrt(target.x * target.x + target.y * target.y);
					if (distance > 0)
					{
						target /= distance;
					}
					sf::Vector2f enagePos = enemy->getPos() + target * 50.0f;
					m_clusterTargets.push_back(enagePos);
				}
			}
		}
		else if (m_convergingState == ConvergingState::Engaging)
		{
			updateConvergingFormation(playerPos, deltaTime);
			for (int i = 0; i < m_enemies.size(); i++)
			{
				auto* behaviour = dynamic_cast<CirclePointBehaviour*>(m_enemies[i]->getBehaviour());
				if (behaviour)
				{
					behaviour->setTarget(m_clusterTargets[i]);
				}
			}
		}
	}
}

void Horde::render(sf::RenderWindow& window)
{
	for (auto& enemy : m_enemies)
	{
		if(enemy->getType() == EnemyType::Archer)
		{
			Archer* archer = dynamic_cast<Archer*>(enemy.get());
			archer->drawArrows(window);
		}
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

	for (auto& enemy : m_enemies) {
		if (enemy == m_leader.lock()) {
			if (enemy->getType() == EnemyType::Thief)
			{
				enemy->setBehaviour(std::make_unique<AmbushBehaviour>());
			}
			else {
				enemy->setBehaviour(std::make_unique<SeekBehaviour>());
			}
		}
		else {
			if (enemy->getType() == EnemyType::Thief)
			{
				enemy->setBehaviour(std::make_unique<AmbushBehaviour>());
			}
			else
			{
				enemy->setBehaviour(std::make_unique<FollowLeaderBehaviour>(m_leader));
			}
		}
	}
}

void Horde::updateCircleFormation(sf::Vector2f playerPos, float deltaTime)
{
	if (m_circleState == CircleState::ClosingIn)
	{
		std::cout << "Shrinking radius: " << m_currentRadius << std::endl;

		float shrinkSpeed = 20.5f;
		if (m_currentRadius > m_targetRadius)
		{
			m_currentRadius -= shrinkSpeed * deltaTime;
			if (m_currentRadius < m_targetRadius)
			{
				m_currentRadius = m_targetRadius;
			}
		}
	}

	m_circleTargets.clear();
	int count = m_enemies.size();
	float angleDivder = 2 * PI / count;
	for (int i = 0; i < count; i++)
	{
		float angle = i * angleDivder;
		float x = playerPos.x + std::cos(angle) * m_currentRadius;
		float y = playerPos.y + std::sin(angle) * m_currentRadius;
		m_circleTargets.emplace_back(x, y);
	}
}

void Horde::updateConvergingFormation(sf::Vector2f playerPos, float deltaTime)
{
	if (m_convergingState == ConvergingState::MovingToClusters)
	{
		m_clusterTargets.clear();

		int numClusters = 3;
		float clusterRadius = 300.f;
		int count = m_enemies.size();
		int enemiesPerCluster = count / numClusters;
		int remaining = count;

		int index = 0;
		for (int c = 0; c < numClusters; c++)
		{
			// Position each cluster around the player
			float angle = (2 * PI / numClusters) * c;
			sf::Vector2f clusterOrigin = {
				playerPos.x + std::cos(angle) * clusterRadius,
				playerPos.y + std::sin(angle) * clusterRadius
			};

			int thisClusterCount;
			if (c == numClusters - 1) {
				thisClusterCount = remaining;
			}
			else {
				thisClusterCount = enemiesPerCluster;
			}
			remaining -= thisClusterCount;

			for (int i = 0; i < thisClusterCount; i++)
			{
				float offsetAngle = static_cast<float>(rand()) / RAND_MAX * 2 * PI;
				float offsetDistance = static_cast<float>(rand()) / RAND_MAX * 40.f;

				float x = clusterOrigin.x + std::cos(offsetAngle) * offsetDistance;
				float y = clusterOrigin.y + std::sin(offsetAngle) * offsetDistance;

				m_clusterTargets.emplace_back(x, y);
				index++;
			}
		}
	}
	else if (m_convergingState == ConvergingState::Engaging)
	{
		std::cout << "Horde is engaging" << std::endl;
		float shrinkSpeed = 30.0f;

		for (int i = 0; i < m_clusterTargets.size(); ++i)
		{
			sf::Vector2f& target = m_clusterTargets[i];
			sf::Vector2f toPlayer = playerPos - target;
			float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

			if (dist > 5.f)
			{
				toPlayer /= dist;
				target += toPlayer * shrinkSpeed * deltaTime;
			}
		}

		// Check if player moved too far away from the closest cluster target
		float minDistance = std::numeric_limits<float>::max();
		for (int i = 0; i < m_clusterTargets.size(); ++i)
		{
			sf::Vector2f toPlayer = playerPos - m_clusterTargets[i];
			float distance = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
			if (distance < minDistance)
			{
				minDistance = distance;
			}
		}

		if (minDistance > 200.f)
		{
			std::cout << "Player moved too far from clusters\n";

			std::shared_ptr<Enemy> leader = m_leader.lock();

			for (auto& enemy : m_enemies)
			{
				if (enemy->getType() == EnemyType::Thief)
				{
					enemy->setBehaviour(std::make_unique<AmbushBehaviour>());
				}
				else
				{
					if (enemy == leader)
					{
						enemy->setBehaviour(std::make_unique<SeekBehaviour>());
					}
					else
					{
						enemy->setBehaviour(std::make_unique<FollowLeaderBehaviour>(m_leader));
					}
				}
			}
			m_converging = false;
			m_convergingState = ConvergingState::MovingToClusters;
			m_clusterTargets.clear();
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
				if (distanceBetween < 50.0f && distanceBetween > 0.0f)
				{
					seperationForce += vectorBetween / distanceBetween;
				}
			}

		}
		// normalise seperation force and multiply
		seperationForce = normalise(seperationForce) * 2.0f;
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
        int type = rand() % 4;
        types.push_back(type);
    }
    return types;
}


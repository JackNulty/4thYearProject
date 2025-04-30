#include "Game.h"

Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef),
    fixedTimeStep(1.0f / 60.0f),// 60fps fixed update
    m_timeAccumulator(0.0f),
    m_isRunning(true),
    m_horde(enemyCount, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), HordeFormation::Cluster, enemySpacing),
    cameraView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
{
    if (!cursorTexture.loadFromFile("ASSETS/UI/Arrow4.png"))
    {
        std::cout << "Error loading cursor texture\n";
    }
    window.setMouseCursorVisible(false);
    m_cursorSprite.setTexture(cursorTexture);
	m_cursorSprite.setOrigin(m_cursorSprite.getGlobalBounds().width / 2, m_cursorSprite.getGlobalBounds().height / 2);
    
    cameraView.setCenter(m_player.getPos());

	// Load the map
    m_map = std::vector<std::vector<int>>(MAP_WIDTH + MAP_OFFSET_X, std::vector<int>(MAP_HEIGHT + MAP_OFFSET_Y));
    m_tileVertices.setPrimitiveType(sf::Quads);
	for (int y = 0; y < MAP_HEIGHT + MAP_OFFSET_Y; y++)
	{
		for (int x = 0; x < MAP_WIDTH + MAP_OFFSET_X; x++)
		{
			m_map[x][y] = rand() % 4; // mix tile types
		}
	}
	if (!m_mapTexture.loadFromFile("ASSETS/UI/Beach_Decor_Tiles.png"))
	{
		std::cout << "Error loading map tilesheet\n";
	}
    for (int i = 0; i < 4; i++)
    {
		tiles[i].setTexture(m_mapTexture);
		tiles[i].setTextureRect(sf::IntRect((i % 2) * 16, (i / 2) * 16, 16, 16));
		tiles[i].setScale(2.f, 2.f);
    }
}

void Game::run() 
{
    sf::Clock clock;
    while (m_isRunning && !m_exiting) {
        sf::Time deltaTime = clock.restart();
        m_timeAccumulator += deltaTime.asSeconds();

        handleEvents();

        while (m_timeAccumulator >= fixedTimeStep) {
            fixedUpdate(fixedTimeStep);
            m_timeAccumulator -= fixedTimeStep;
        }

        update(deltaTime.asSeconds());
        render();
    }
}

void Game::exitToMenu() 
{
    m_exiting = true;
}

void Game::handleEvents() 
{
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            exitToMenu();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
        {
            if(m_horde.m_currentFormation == HordeFormation::Circle)
                m_horde.setFormation(HordeFormation::Grid, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), 50);
            else if (m_horde.m_currentFormation == HordeFormation::Grid)
                m_horde.setFormation(HordeFormation::Circle, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), 50);
        }
    }
}

void Game::fixedUpdate(float deltaTime) 
{
    //std::cout << "Fixed Update: " << deltaTime << " seconds\n";
    ResourceManager::getParticleManager().update(deltaTime);
    m_player.fixedUpdate(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)), cameraView);
    m_gameWorld.fixedUpdate(deltaTime);
    m_horde.fixedUpdate(deltaTime, m_player.getPos(), cameraView);
    handleBulletCollisions();
    handleArrowCollisions();
    handleSwordCollisions();
    handleShurikenCollisions();
	handleDynamiteCollisions();
    playerCollision();
    if (m_horde.m_enemies.empty())
    {
        spawnWave();
        if (m_player.getLives() < 6)
        {
            m_player.addLife();
        }
    }
    for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();) {
        auto leader = m_horde.getLeader().lock();
        if((*enemy)->getType() == EnemyType::Archer)
		{
			auto archer = dynamic_cast<Archer*>(enemy->get());
			archer->attack(m_player.getPos());
		}
        if ((*enemy)->isDead())
        {
            bool wasLeader = (leader && enemy->get() == leader.get());
            enemy = m_horde.m_enemies.erase(enemy);

            if (wasLeader) {
                m_horde.setLeader();
            }
        }
		else
		{
			enemy++;
		}
    }
    cameraUpdate(deltaTime);
}

void Game::update(float deltaTime) 
{
    //std::cout << "Regular Update: " << deltaTime << " seconds\n";
    m_player.update(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)), cameraView);
    m_gameWorld.update(deltaTime);
    m_horde.update(deltaTime, m_player.getPos());
	m_cursorSprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
	m_cursorSprite.setScale(0.5f, 0.5f);
	updateMap();
}

void Game::render() 
{
    window.setView(cameraView);
    window.clear(sf::Color(210, 180, 140));
    // Draw the map
    window.draw(m_tileVertices, &m_mapTexture);
    m_gameWorld.render(window);
    m_horde.render(window);
    m_player.render(window, cameraView);
    ResourceManager::getParticleManager().render(window);
	window.draw(m_cursorSprite);
    window.display();
}

void Game::updateMap()
{
    static const int TILE_SIZE = 32; // doubled size 
    static const int TILESHEET_TILE_SIZE = 16; // original size 

    static int tilesOnScreenX = (WINDOW_WIDTH / TILE_SIZE) + 4;
    static int tilesOnScreenY = (WINDOW_HEIGHT / TILE_SIZE) + 4;

    static bool firstRun = true;
    if (firstRun)
    {
        m_tileVertices.setPrimitiveType(sf::Quads);
        firstRun = false;
    }

    if (cameraView.getCenter() == lastCameraPos)
        return;

    lastCameraPos = cameraView.getCenter();

    sf::Vector2f cameraPos = cameraView.getCenter();
    sf::Vector2f cameraSize = cameraView.getSize();

    sf::Vector2f topLeft(
        cameraPos.x - cameraSize.x / 2.f,
        cameraPos.y - cameraSize.y / 2.f
    );

    int firstTileX = static_cast<int>(std::floor(topLeft.x / TILE_SIZE));
    int firstTileY = static_cast<int>(std::floor(topLeft.y / TILE_SIZE));

    m_tileVertices.clear();
    m_tileVertices.resize(tilesOnScreenX * tilesOnScreenY * 4);

    int index = 0;
    for (int y = 0; y < tilesOnScreenY; ++y)
    {
        for (int x = 0; x < tilesOnScreenX; ++x)
        {
			// Calculate the world tile coordinates
            int worldTileX = firstTileX + x;
            int worldTileY = firstTileY + y;

			// Check if the tile is within the bounds of the map
            int mapArrayX = worldTileX + MAP_OFFSET_X;
            int mapArrayY = worldTileY + MAP_OFFSET_Y;

			// make sure array lookup is within bounds
            if (mapArrayX >= 0 && mapArrayX < m_map.size() && mapArrayY >= 0 && mapArrayY < m_map[0].size())
            {
				// Get the tile type from the map
                int tileTypeIndex = m_map[mapArrayX][mapArrayY];

				// Set the texture rect for the tile
                int tilesetColumn = tileTypeIndex % 2;
                int tilesetRow = tileTypeIndex / 2;

				// Calculate the world position of the tile
                float worldPosX = worldTileX * TILE_SIZE;
                float worldPosY = worldTileY * TILE_SIZE;

				// get pointers to the current quad
                sf::Vertex* currentQuad = &m_tileVertices[index * 4];

				// Set the position and texture coordinates for each vertex
				currentQuad[0].position = sf::Vector2f(worldPosX, worldPosY); // top left
				currentQuad[1].position = sf::Vector2f(worldPosX + TILE_SIZE, worldPosY); // top right
				currentQuad[2].position = sf::Vector2f(worldPosX + TILE_SIZE, worldPosY + TILE_SIZE); // bottom right
				currentQuad[3].position = sf::Vector2f(worldPosX, worldPosY + TILE_SIZE); // bottom left

				// Set the texture coordinates for each vertex
				currentQuad[0].texCoords = sf::Vector2f(tilesetColumn * TILESHEET_TILE_SIZE, tilesetRow * TILESHEET_TILE_SIZE); // top left
				currentQuad[1].texCoords = sf::Vector2f((tilesetColumn + 1) * TILESHEET_TILE_SIZE, tilesetRow * TILESHEET_TILE_SIZE); // top right
				currentQuad[2].texCoords = sf::Vector2f((tilesetColumn + 1) * TILESHEET_TILE_SIZE, (tilesetRow + 1) * TILESHEET_TILE_SIZE); // bottom right
				currentQuad[3].texCoords = sf::Vector2f(tilesetColumn * TILESHEET_TILE_SIZE, (tilesetRow + 1) * TILESHEET_TILE_SIZE); // bottom left

                index++;
            }
        }
    }
}

void Game::cameraUpdate(float deltaTime)
{
	if (m_player.isShaking)
	{
		m_player.shakeTimer += deltaTime;
		if (m_player.shakeTimer >= m_player.shakeDuration)
		{
			m_player.isShaking = false;
			m_player.shakeTimer = 0.0f;
			cameraView.setCenter(m_player.getPos());
		}
		else
		{
			float offsetX = (rand() % static_cast<int>(m_player.shakeMagnitude)) - (m_player.shakeMagnitude / 2);
			float offsetY = (rand() % static_cast<int>(m_player.shakeMagnitude)) - (m_player.shakeMagnitude / 2);
			cameraView.setCenter(m_player.getPos().x + offsetX, m_player.getPos().y + offsetY);
		}
	}
    else {
		cameraView.setCenter(m_player.getPos());
    }
}

void Game::handleBulletCollisions()
{
    auto& bullets = m_player.getBullets();
    // iterator based loop for grunts as the size of horde is varaible
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        bool bulletHit = false;
        // iterator based loop for grunts as the size of horde is varaible
        for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();) {
            if (bullet->getBounds().intersects((*enemy)->getBounds())) {
                std::cout << "Grunt hit" << std::endl;

                (*enemy)->dealDamage();

                ParticleManager& particleManager = ResourceManager::getParticleManager();
                std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
                    "grunt_hit", 25, (*enemy)->getPos());
                system->configure(200.f, 0.4f, 2.f, sf::Color::Red);
                std::cout << "Added new particle system: grunt_hit\n";

                auto leader = m_horde.getLeader().lock();
                if ((*enemy)->isDead())
                {
                    bool wasLeader = (leader && enemy->get() == leader.get());
                    enemy = m_horde.m_enemies.erase(enemy);

                    if (wasLeader) {
                        m_horde.setLeader();
                    }
                }
                bulletHit = true;
                break;
            }
            else {
                enemy++;
            }
        }

        // remove bulet if it collides
        if (bulletHit)
        {
            bullet = bullets.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

void Game::handleArrowCollisions()
{
    // use dynamic cast to get the selected weapon to get its unique ammo type
    auto* selectedWeapon = m_player.m_weaponInventory.getSelectedWeapon();
    Bow* bow = dynamic_cast<Bow*>(selectedWeapon);
    if (!bow)
    {
        //std::cout << "No bow equipped skipping arrow collision checks.\n";
        return; 
    }
    auto& arrows = bow->getArrows();
	// iterator based loop for grunts as the size of horde is varaible
	for (auto arrow = arrows.begin(); arrow != arrows.end();)
	{
		bool arrowHit = false;
		// iterator based loop for grunts as the size of horde is varaible
		for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();) {
			if (arrow->getBounds().intersects((*enemy)->getBounds())) {
				std::cout << "Grunt hit" << std::endl;

                (*enemy)->dealDamage();

                ParticleManager& particleManager = ResourceManager::getParticleManager();
                std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
                    "grunt_hit", 10, (*enemy)->getPos());
                system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
                std::cout << "Added new particle system: grunt_hit\n";

                auto leader = m_horde.getLeader().lock();
                if ((*enemy)->isDead())
                {
                    bool wasLeader = (leader && enemy->get() == leader.get());
                    enemy = m_horde.m_enemies.erase(enemy);

                    if (wasLeader) {
                        m_horde.setLeader();
                    }
                }
                else
                {
                    enemy++;
                }
                arrowHit = true;
                break;
			}
			else {
				enemy++;
			}
		}
		// remove arrow if it collides
		if (arrowHit)
		{
			arrow = arrows.erase(arrow);
		}
		else {
			++arrow;
		}
	}

}

void Game::handleSwordCollisions()
{
    //use dynamic cast to get the selected weapon to get its unique type
    auto* selectedWeapon = m_player.m_weaponInventory.getSelectedWeapon();
    Sword* sword = dynamic_cast<Sword*>(selectedWeapon);
    if(!sword)
	{
		//std::cout << "No sword equipped skipping sword collision checks.\n";
		return;
	}
    for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();)
	{
		if (sword->getBounds().intersects((*enemy)->getBounds()) && sword->getAttackFlag())
		{
			std::cout << "Grunt hit" << std::endl;

			(*enemy)->dealDamage();

			ParticleManager& particleManager = ResourceManager::getParticleManager();
			std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
				"grunt_hit", 10, (*enemy)->getPos());
			system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
			std::cout << "Added new particle system: grunt_hit\n";

			auto leader = m_horde.getLeader().lock();
			if ((*enemy)->isDead())
			{
				bool wasLeader = (leader && enemy->get() == leader.get());
				enemy = m_horde.m_enemies.erase(enemy);

				if (wasLeader) {
					m_horde.setLeader();
				}
			}
			else
			{
				enemy++;
			}
		}
		else
		{
			enemy++;
		}
	}
}

void Game::handleShurikenCollisions()
{
    //use dynamic cast to get the selected weapon to get its unique type
	auto* selectedWeapon = m_player.m_weaponInventory.getSelectedWeapon();
	Shuriken* shuriken = dynamic_cast<Shuriken*>(selectedWeapon);
	if (!shuriken)
	{
		//std::cout << "No shuriken equipped skipping shuriken collision checks.\n";
		return;
	}

    if (shuriken->cooldownTimer > 0)
    {
        return; // dont check for collisions if shuriken is on cooldown
    }
	for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();)
	{
		if (shuriken->getBounds().intersects((*enemy)->getBounds()) && shuriken->getAttackFlag())
		{
			std::cout << "Grunt hit" << std::endl;
            sf::Vector2f enemyPosition = (*enemy)->getPos();

            (*enemy)->dealDamage();

            ParticleManager& particleManager = ResourceManager::getParticleManager();
            std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
                "grunt_hit", 10, (*enemy)->getPos());
            system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
            std::cout << "Added new particle system: grunt_hit\n";

            sf::Vector2f newTarget;
            bool foundTarget = false;
            for (auto& potentialTarget : m_horde.m_enemies)
            {
                if (potentialTarget.get() != (*enemy).get())
                {
                    newTarget = potentialTarget->getPos();
                    foundTarget = true;
                    break;
                }
            }

            auto leader = m_horde.getLeader().lock();
            if ((*enemy)->isDead())
            {
                bool wasLeader = (leader && enemy->get() == leader.get());
                enemy = m_horde.m_enemies.erase(enemy);

                if (wasLeader) {
                    m_horde.setLeader();
                }
            }
            else
            {
                enemy++;
            }

            //ricochet shuriken
            if (foundTarget)
            {
                shuriken->ricochet(newTarget);
            }
            else {
                selectedWeapon->reset();
            }
            break;
		}
		else
		{
			enemy++;
		}
	}

}

void Game::handleDynamiteCollisions()
{
	//use dynamic cast to get the selected weapon to get its unique type
	auto* selectedWeapon = m_player.m_weaponInventory.getSelectedWeapon();
	Dynamite* dynamite = dynamic_cast<Dynamite*>(selectedWeapon);
	if (!dynamite)
	{
		//std::cout << "No dynamite equipped skipping dynamite collision checks.\n";
		return;
	}
	for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();)
	{
		if (dynamite->m_explosionCircle.getGlobalBounds().intersects((*enemy)->getBounds()) && dynamite->getAttackFlag())
		{
			std::cout << "Grunt hit" << std::endl;
			(*enemy)->dealDamage();
			ParticleManager& particleManager = ResourceManager::getParticleManager();
			std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
				"grunt_hit", 10, (*enemy)->getPos());
			system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
			std::cout << "Added new particle system: grunt_hit\n";
			auto leader = m_horde.getLeader().lock();
			if ((*enemy)->isDead())
			{
				bool wasLeader = (leader && enemy->get() == leader.get());
				enemy = m_horde.m_enemies.erase(enemy);
				if (wasLeader) {
					m_horde.setLeader();
				}
			}
			else
			{
				enemy++;
			}
		}
		else
		{
			enemy++;
		}
	}
}

void Game::playerCollision()
{
    // iterator based loop for enemies to check if player collides with enemies
    for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();) {
        if ((*enemy)->getType() == EnemyType::Archer)
        {
            auto archer = dynamic_cast<Archer*>(enemy->get());
            for(auto arrow = archer->getArrowVector().begin(); arrow != archer->getArrowVector().end();)
			{
				if (arrow->getBounds().intersects(m_player.getBounds()))
				{
					m_player.removeLife();
					arrow = archer->getArrowVector().erase(arrow);
				}
				else {
					arrow++;
				}
			}
        }
        if (m_player.getBounds().intersects((*enemy)->getBounds()))
        {
            (*enemy)->attack(m_player.getPos()); 
            m_player.removeLife();
            enemy++;
        }
        else
        {
            enemy++;
        }
	}
}

void Game::spawnWave()
{
    waveNum++;
    // increase enemies by 10% every wave
    int newEnemyCount = enemyCount * std::pow(1.1, waveNum - 1);
    std::cout << "Wave " << waveNum << "now spawning " << newEnemyCount << " enemies in next wave" << std::endl;
    HordeFormation Formation;
    // cycle through formations 
    if (waveNum % 3 == 0)
        Formation = HordeFormation::Circle;
    else if (waveNum % 3 == 2)
        Formation = HordeFormation::Grid;
    else
        Formation = HordeFormation::Cluster;
    m_horde = Horde(newEnemyCount, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), Formation, enemySpacing);
}

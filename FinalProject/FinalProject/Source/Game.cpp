#include "Game.h"

Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef),
    fixedTimeStep(1.0f / 60.0f),// 60fps fixed update
    m_timeAccumulator(0.0f),
    m_isRunning(true),
    m_horde(enemyCount, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), HordeFormation::Cluster, enemySpacing),
	m_heavy(700, 100),
    m_archer(700, 300),
    cameraView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT))
{
	m_heavy.setBehaviour(std::make_unique<SeekBehaviour>());
    m_archer.setBehaviour(std::make_unique<KeepDistance>());
    
    cameraView.setCenter(m_player.getPos());
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
	//m_heavy.fixedUpdate(deltaTime, m_player.getPos(), cameraView);
    //m_archer.fixedUpdate(deltaTime, m_player.getPos(), cameraView);
    handleBulletCollisions();
    handleArrowCollisions();
    playerCollision();
    m_archer.attack(m_player.getPos());
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
}

void Game::update(float deltaTime) 
{
    //std::cout << "Regular Update: " << deltaTime << " seconds\n";
    m_player.update(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)), cameraView);
    m_gameWorld.update(deltaTime);
    //m_archer.update(deltaTime);
    m_horde.update(deltaTime, m_player.getPos());
	//m_heavy.update(deltaTime);
    cameraView.setCenter(m_player.getPos());
}

void Game::render() 
{
    window.setView(cameraView);
    window.clear(sf::Color(210, 180, 140));
    m_gameWorld.render(window);
    m_player.render(window, cameraView);
    m_horde.render(window);
	//m_heavy.render(window);
    //m_archer.render(window);
    //m_archer.drawArrows(window);
    ResourceManager::getParticleManager().render(window);
    window.display();
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
        std::cout << "No bow equipped skipping arrow collision checks.\n";
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

        if (arrow->getBounds().intersects(m_heavy.getBounds()))
        {
            m_heavy.dealDamage();
            std::cout << "Heavy hit" << std::endl;
            ParticleManager& particleManager = ResourceManager::getParticleManager();
            std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
                "heavy_hit", 10, m_heavy.getPos());
            system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
            std::cout << "Added new particle system: heavy_hit\n";
			arrowHit = true;
        }
        if (arrow->getBounds().intersects(m_archer.getBounds()))
        {
            m_archer.dealDamage();
            std::cout << "Archer hit" << std::endl;
            ParticleManager& particleManager = ResourceManager::getParticleManager();
            std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
                "archer_hit", 10, m_archer.getPos());
            system->configure(200.f, 0.4f, 1.f, sf::Color::Red);
            std::cout << "Added new particle system: archer_hit\n";
            arrowHit = true;
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

void Game::playerCollision()
{
    // iterator based loop for enemies to check if player collides with enemies
    for (auto enemy = m_horde.m_enemies.begin(); enemy != m_horde.m_enemies.end();) {
        if (m_player.getBounds().intersects((*enemy)->getBounds()))
        {
            (*enemy)->attack(m_player.getPos()); 
            enemy++;
        }
        else
        {
            enemy++;
        }
	}
    if(m_heavy.getBounds().intersects(m_player.getBounds()))
	{
		if(m_heavy.canAttack())
		{
            m_heavy.attack(m_player.getPos());
			m_player.removeLife();
		}
	}
    for (auto arrow = m_archer.getArrowVector().begin(); arrow != m_archer.getArrowVector().end();)
    {
        if (arrow->getBounds().intersects(m_player.getBounds()))
        {
            m_player.removeLife();
            arrow = m_archer.getArrowVector().erase(arrow);
        }
        else {
            arrow++;
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

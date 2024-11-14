#include "Game.h"

Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef),
    fixedTimeStep(1.0f / 60.0f),// 60fps fixed update
    m_timeAccumulator(0.0f),
    m_isRunning(true),
    m_horde(enemyCount, EnemyBehaviourTypes::Arrive, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), HordeFormation::Cluster, enemySpacing) 
{
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
    m_player.fixedUpdate(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    m_gameWorld.fixedUpdate(deltaTime);
    m_horde.fixedUpdate(deltaTime, m_player.getPos());
    handleBulletCollisions();
    if (m_horde.m_grunts.empty())
    {
        spawnWave();
    }
}

void Game::update(float deltaTime) 
{
    //std::cout << "Regular Update: " << deltaTime << " seconds\n";
    m_player.update(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    m_gameWorld.update(deltaTime);
    m_horde.update(deltaTime);
}

void Game::render() 
{
    window.clear();
    m_gameWorld.render(window);
    m_player.render(window);
    m_horde.render(window);
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
        for (auto grunt = m_horde.m_grunts.begin(); grunt != m_horde.m_grunts.end();) {
            if (bullet->getBounds().intersects(grunt->getBounds())) {
                std::cout << "Grunt hit" << std::endl;
                grunt = m_horde.m_grunts.erase(grunt);
                bulletHit = true;
                break; 
            }
            else {
                grunt++;
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

void Game::spawnWave()
{
    waveNum++;
    int newEnemyCount = enemyCount * std::pow(1.1, waveNum - 1);
    std::cout << "Wave" << waveNum << "now spawning " << newEnemyCount << "enemies in next wave" << std::endl;
    HordeFormation Formation;
    if (waveNum % 3 == 0)
        Formation = HordeFormation::Circle;
    else if (waveNum % 3 == 2)
        Formation = HordeFormation::Grid;
    else
        Formation = HordeFormation::Cluster;
    m_horde = Horde(newEnemyCount, EnemyBehaviourTypes::Arrive, sf::Vector2f(randomPosition(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))), Formation, enemySpacing);
}

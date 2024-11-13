#include "Game.h"

Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef),
    fixedTimeStep(1.0f / 60.0f),
    m_timeAccumulator(0.0f),
    m_isRunning(true),
    m_grunt(EnemyBehaviourTypes::Seek, 500, 500),
    m_horde(12, EnemyBehaviourTypes::Seek, sf::Vector2f(300,300))
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
    }
}

void Game::fixedUpdate(float deltaTime) 
{
    //std::cout << "Fixed Update: " << deltaTime << " seconds\n";
    m_player.fixedUpdate(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    m_gameWorld.fixedUpdate(deltaTime);
    m_horde.fixedUpdate(deltaTime, m_player.getPos());
    m_grunt.fixedUpdate(deltaTime, m_player.getPos());
    handleBulletCollisions();
}

void Game::update(float deltaTime) 
{
    //std::cout << "Regular Update: " << deltaTime << " seconds\n";
    m_player.update(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    m_gameWorld.update(deltaTime);
    m_horde.update(deltaTime);
    m_grunt.update(deltaTime);
}

void Game::render() 
{
    window.clear();
    m_gameWorld.render(window);
    m_player.render(window);
    m_horde.render(window);
    m_grunt.render(window);
    window.display();
}

void Game::handleBulletCollisions()
{
    auto& bullets = m_player.getBullets();
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        bool bulletHit = false;
        if (bullet->getBounds().intersects(m_grunt.getBounds()))
        {
            std::cout << "Grunt hit" << std::endl;
            bulletHit = true;
            break;
        }
        if (bulletHit)
        {
            bullet = bullets.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

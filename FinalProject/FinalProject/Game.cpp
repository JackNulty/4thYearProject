#include "Game.h"

Game::Game(sf::RenderWindow& windowRef)
    : window(windowRef),
    fixedTimeStep(1.0f / 60.0f),
    timeAccumulator(0.0f),
    isRunning(true),
    grunt(EnemyBehaviourTypes::Seek){
}

void Game::run() 
{
    sf::Clock clock;
    while (isRunning && !exiting) {
        sf::Time deltaTime = clock.restart();
        timeAccumulator += deltaTime.asSeconds();

        handleEvents();

        while (timeAccumulator >= fixedTimeStep) {
            fixedUpdate(fixedTimeStep);
            timeAccumulator -= fixedTimeStep;
        }

        update(deltaTime.asSeconds());
        render();
    }
}

void Game::exitToMenu() 
{
    exiting = true;
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
    player.fixedUpdate(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    gameWorld.fixedUpdate(deltaTime);
    grunt.fixedUpdate(deltaTime, player.getPos());
    handleBulletCollisions();
}

void Game::update(float deltaTime) 
{
    //std::cout << "Regular Update: " << deltaTime << " seconds\n";
    player.update(deltaTime, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    gameWorld.update(deltaTime);
    grunt.update(deltaTime);
}

void Game::render() 
{
    window.clear();
    gameWorld.render(window);
    player.render(window);
    grunt.render(window);
    window.display();
}

void Game::handleBulletCollisions()
{
    auto& bullets = player.getBullets();
    for (auto bullet = bullets.begin(); bullet != bullets.end();)
    {
        bool bulletHit = false;
        if (bullet->getBounds().intersects(grunt.getBounds()))
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

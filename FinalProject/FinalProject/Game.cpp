#include "Game.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game"),
    fixedTimeStep(1.0f / 60.0f),
    timeAccumulator(0.0f),
    isRunning(true),
    grunt(EnemyBehaviourTypes::Seek){
}

void Game::run() {
    sf::Clock clock;
    while (isRunning) {
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

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            window.close();
    }
}

void Game::fixedUpdate(float deltaTime) {
    std::cout << "Fixed Update: " << deltaTime << " seconds\n";
    player.fixedUpdate(deltaTime);
    gameWorld.fixedUpdate(deltaTime);
    grunt.fixedUpdate(deltaTime, player.getPos());
}

void Game::update(float deltaTime) {
    std::cout << "Regular Update: " << deltaTime << " seconds\n";
    player.update(deltaTime);
    gameWorld.update(deltaTime);
    grunt.update(deltaTime);
}

void Game::render() {
    window.clear();
    gameWorld.render(window);
    player.render(window);
    grunt.render(window);
    window.display();
}
#include "Game.h"

Game::Game()
    : window(sf::VideoMode(1200, 800), "SFML Game"),
    fixedTimeStep(1.0f / 60.0f),
    timeAccumulator(0.0f),
    isRunning(true) {
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
    }
}

void Game::fixedUpdate(float deltaTime) {
    std::cout << "Fixed Update: " << deltaTime << " seconds\n";
}

void Game::update(float deltaTime) {
    std::cout << "Regular Update: " << deltaTime << " seconds\n";
}

void Game::render() {
    window.clear();
    window.display();
}
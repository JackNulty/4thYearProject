#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow& windowRef)
    : game(windowRef), gameStarted(false), gameExited(false) {
}

void GameplayScene::handleEvent(sf::Event& event)
{ 
    if (event.type == sf::Event::Closed) {
        gameExited = true;
    }
}

void GameplayScene::update(float deltaTime) 
{
    if (gameExited) {
        SceneManager::getInstance().changeScene("MainMenu");
        gameExited = false; 
    }
}

void GameplayScene::draw(sf::RenderWindow& window) { }

void GameplayScene::startGame()
{
    if (!gameStarted) {
        game.run();
        gameStarted = true;
    }
}

#include "GameplayScene.h"

GameplayScene::GameplayScene(sf::RenderWindow& windowRef)
    : game(windowRef), gameStarted(false), gameExited(false), window(windowRef) {
}

void GameplayScene::handleEvent(sf::Event& event)
{ 
    if (event.type == sf::Event::Closed) {
		window.close();
		gameExited = true;
    }
}

void GameplayScene::update(float deltaTime) 
{
    if (gameExited) {
		gameStarted = false;
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

void GameplayScene::onEnter()
{
}

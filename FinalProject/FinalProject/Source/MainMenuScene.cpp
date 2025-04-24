#include "MainMenuScene.h"
#include "SceneManager.h"

MainMenuScene::MainMenuScene(sf::RenderWindow& window)
    : window(window) {
    loadAssets();

    m_startButtonSprite.setTexture(m_buttonTexture);
    m_startButtonSprite.setPosition(300, 250);
}

void MainMenuScene::handleEvent(sf::Event& event) 
{
    if (event.type == sf::Event::Closed) {
        window.close();
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (m_startButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                SceneManager::getInstance().changeScene("Gameplay");
            }
        }
    }
}

void MainMenuScene::update(float deltaTime) 
{
}

void MainMenuScene::draw(sf::RenderWindow& window) 
{
    std::cout << "Drawing MainMenuScene..." << std::endl;
    //window.clear();
    window.draw(m_startButtonSprite);
    //window.display();
}

void MainMenuScene::onEnter()
{
	loadAssets();
    m_startButtonSprite.setTexture(m_buttonTexture);
    m_startButtonSprite.setPosition(300, 250);
}

void MainMenuScene::loadAssets()
{
    if (!m_buttonTexture.loadFromFile("ASSETS/Play-Button.png")) { 
        std::cout << "failed to load start button sprite" << std::endl;
    }
}

#pragma once
#include "Scene.h"

class MainMenuScene : public Scene {
public:
    MainMenuScene(sf::RenderWindow& window);
    void handleEvent(sf::Event& event) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::RenderWindow& window;
    sf::Texture m_buttonTexture; 
    sf::Sprite m_startButtonSprite;
    void loadAssets();
};
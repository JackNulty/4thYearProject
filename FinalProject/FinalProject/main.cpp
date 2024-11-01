#include "globals.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameplayScene.h"

int main() {

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Final Project");

    //scenes init 
    SceneManager::getInstance().addScene("MainMenu", std::make_unique<MainMenuScene>(window));
    SceneManager::getInstance().addScene("Gameplay", std::make_unique<GameplayScene>(window));
    //Start on main menu
    SceneManager::getInstance().changeScene("MainMenu");

    sf::Clock clock;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (Scene* scene = SceneManager::getInstance().getCurrentScene()) {
                scene->handleEvent(event);
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (Scene* scene = SceneManager::getInstance().getCurrentScene()) {
            scene->update(deltaTime);
        }

        window.clear(); 
        if (Scene* scene = SceneManager::getInstance().getCurrentScene()) {
            scene->draw(window);
        }
        window.display();
    }

    return 0;
}
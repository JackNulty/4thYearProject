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
    sf::Sprite m_cursorSprite;
	if (!cursorTexture.loadFromFile("ASSETS/UI/Arrow4.png"))
	{
		std::cout << "Error loading cursor texture\n";
	}
    window.setMouseCursorVisible(false);
	m_cursorSprite.setTexture(cursorTexture);
	m_cursorSprite.setOrigin(m_cursorSprite.getGlobalBounds().width / 2, m_cursorSprite.getGlobalBounds().height / 2);
	m_cursorSprite.setScale(0.5f, 0.5f);

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
		// Update cursor position
		m_cursorSprite.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

        window.clear(); 
        if (Scene* scene = SceneManager::getInstance().getCurrentScene()) {
            scene->draw(window);
        }
		window.draw(m_cursorSprite);
        window.display();
    }

    return 0;
}
#include "SceneManager.h"
#include "GameplayScene.h"

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) 
{
    m_scenes[name] = std::move(scene);
}

void SceneManager::changeScene(const std::string& name) 
{
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
        m_currentScene = it->second.get();
		m_currentScene->onEnter();

        //check if the current scene is gameplay to start the game.run()
        if (GameplayScene* gameplayScene = dynamic_cast<GameplayScene*>(m_currentScene)) {
            gameplayScene->startGame();
        }
    }
}

Scene* SceneManager::getCurrentScene() 
{
    return m_currentScene;
}
#include "SceneManager.h"
#include "GameplayScene.h"

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) 
{
    scenes[name] = std::move(scene);
}

void SceneManager::changeScene(const std::string& name) 
{
    auto it = scenes.find(name);
    if (it != scenes.end()) {
        currentScene = it->second.get();

        //check if the current scene is gameplay to start the game.run()
        if (GameplayScene* gameplayScene = dynamic_cast<GameplayScene*>(currentScene)) {
            gameplayScene->startGame();
        }
    }
}

Scene* SceneManager::getCurrentScene() 
{
    return currentScene;
}
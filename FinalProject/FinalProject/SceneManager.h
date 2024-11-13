#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager& getInstance();

    void addScene(const std::string& name, std::unique_ptr<Scene> scene);
    void changeScene(const std::string& name);
    Scene* getCurrentScene();

private:
    SceneManager() = default;

    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
    Scene* m_currentScene = nullptr;
};

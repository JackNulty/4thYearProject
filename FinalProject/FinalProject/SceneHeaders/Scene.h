#pragma once
#include "globals.h"
class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleEvent(sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};

#pragma once
#include "globals.h"
#include "Player.h"
#include "Level.h"

#ifndef GAME_H
#define GAME_H

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    const float fixedTimeStep; 
    float timeAccumulator;
    bool isRunning;

    Player player;
    Level gameWorld;

    void handleEvents();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();
};

#endif


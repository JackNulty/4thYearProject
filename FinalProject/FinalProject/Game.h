#pragma once
#include "globals.h"
#include "Player.h"
#include "Level.h"
#include "Grunt.h"
#include "EnemyBehavioursEnum.h"

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
    Grunt grunt;

    void handleEvents();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();
};

#endif


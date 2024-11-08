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
    Game(sf::RenderWindow& window);
    void run();
    void exitToMenu();

private:
    sf::RenderWindow& window; // window 
    const float fixedTimeStep; 
    float timeAccumulator;
    bool isRunning;
    bool exiting = false;

    Player player;
    Level gameWorld;
    Grunt grunt;

    void handleEvents();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();
    void handleBulletCollisions();
};

#endif


#pragma once
#include "globals.h"
#include "Player.h"
#include "Level.h"
#include "Grunt.h"
#include "EnemyBehavioursEnum.h"
#include "Horde.h"

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
    float m_timeAccumulator;
    bool m_isRunning;
    bool m_exiting = false;
    int waveNum = 1;
    int enemyCount = 10;
    int enemySpacing = 50;

    Player m_player;
    Level m_gameWorld;
    Horde m_horde;

    void handleEvents();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();
    void handleBulletCollisions();
    void spawnWave();
    void playerCollision();
};

#endif


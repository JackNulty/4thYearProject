#pragma once
#include "globals.h"
#include "Player.h"
#include "Level.h"
#include "Grunt.h"
#include "EnemyBehavioursEnum.h"
#include "Horde.h"
#include "Heavy.h"
#include "Archer.h"
#include "Enemy.h"

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

    sf::View cameraView; // viewport for following player
    sf::Sprite m_cursorSprite;
    
    //map
	std::vector<std::vector<int>> m_map;
	sf::Texture m_mapTexture;
    sf::Sprite tiles[4];
    sf::VertexArray m_tileVertices;
    sf::Vector2f lastCameraPos;
    static constexpr int MAP_OFFSET_X = 500;
    static constexpr int MAP_OFFSET_Y = 500;

    void handleEvents();
    void fixedUpdate(float deltaTime);
    void update(float deltaTime);
    void render();
	void cameraUpdate(float deltaTime);
    void handleBulletCollisions();
    void handleArrowCollisions();
    void handleSwordCollisions();
    void handleShurikenCollisions();
	void handleDynamiteCollisions();
    void spawnWave();
    void playerCollision();
    void updateMap();
};

#endif


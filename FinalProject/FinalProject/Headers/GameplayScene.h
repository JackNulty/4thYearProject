#pragma once  
#include "globals.h"  
#include "Scene.h"  
#include "Game.h"  
#include "SceneManager.h"  

class GameplayScene : public Scene {  
public:  
   GameplayScene(sf::RenderWindow& window);  

   void handleEvent(sf::Event& event) override;  
   void update(float deltaTime) override;  
   void draw(sf::RenderWindow& window) override;  
   void startGame();  
   void onEnter() override;

private:  
   Game game;  
   bool gameExited = false;  
   bool gameStarted = false;  
   sf::RenderWindow& window;
};
#pragma once  
#include "globals.h"  
#include "Grunt.h"  
#include "Bullet.h"  
#include "HordeFormationsEnum.h"  
#include "SeekBehaviour.h"  
#include "KeepDistance.h"  
#include "FollowLeaderBehaviour.h"  
#include "Enemy.h"  
#include "Archer.h"  
#include "Heavy.h"  
#include "../Thief.h"  
#include "../CirclePointBehaviour.h"  
#include "Behaviour.h"

// handle cirlce state for horde
enum class CircleState { 
	MovingToPositions, ClosingIn, Idle 
};

enum class ConvergingState {
	MovingToClusters, Engaging 
};

class Horde  
{  
public:  
   Horde(int maxEnemies, sf::Vector2f centreHorde, HordeFormation startFormation, int enemySpacing);  
   std::vector<std::shared_ptr<Enemy>> m_enemies;  
   sf::Clock m_formationClock;  
   std::vector<sf::Vector2f> generateFormation(int maxEnemies, sf::Vector2f centreHorde, int enemySpacing);  
   void update(float deltaTime, sf::Vector2f playerPos);  
   void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView);  
   void render(sf::RenderWindow& window);  
   HordeFormation m_currentFormation;  
   void setFormation(HordeFormation type, sf::Vector2f centreHorde, int enemySpacing);  
   void setLeader();  
   std::weak_ptr<Enemy> getLeader() { return m_leader; }  
   void setCircleFormation(bool circle) { m_circleFormation = circle; }  
   bool getCircleFormation() { return m_circleFormation; }  

private:  
   std::vector<sf::Vector2f> positions;  
   void seperation();  
   std::vector<int> enemyTypes(int MAX_ENEMIES);  
   float radius = 100.0f;  
   std::weak_ptr<Enemy> m_leader;  
   void assignLeader();  
   void updateCircleFormation(sf::Vector2f playerPos, float deltaTime);  
   void updateConvergingFormation(sf::Vector2f playerPos, float deltaTime);
   std::vector<sf::Vector2f> m_circleTargets;  
   std::vector<sf::Vector2f> m_clusterTargets;
   float m_currentRadius;  
   float m_targetRadius;  
   bool m_circleFormation = false; 
   bool m_converging = false;
   CircleState m_circleState = CircleState::Idle;
   ConvergingState m_convergingState = ConvergingState::MovingToClusters;
};

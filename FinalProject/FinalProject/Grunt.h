#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"

class Grunt
{
public:
	Grunt(EnemyBehaviourTypes startBehaviour, float x, float y);
	void update(float deltaTime);
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos);
	void render(sf::RenderWindow& window);
	sf::FloatRect getBounds() const; 
	sf::Vector2f getPos() const;
	void setPos(sf::Vector2f pos);

	sf::Vector2f m_velocity;

private:
	//private functions
	void gruntAnimations();

	//private vars
	sf::Texture *m_gruntTexture;
	sf::Sprite m_gruntSprite;
	EnemyBehaviours m_behaviours;
	EnemyBehaviourTypes m_currentBehaviour;
	float m_speed;
	sf::Vector2f m_acceleration;
	float maxSpeed = 5.0f;
	float maxForce = 0.1f;
	int frameDelay = 5; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
	int frameWidth = 32; // width of each frame
	int frameHeight = 32; // height of each frame

};


#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"
#include "Enemy.h"
#include "Arrow.h"

class Archer : public Enemy {
public:
	Archer(float x, float y);
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
	bool canAttack() const { return m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown; }
	void attack(sf::Vector2f playerPos) override;
	sf::FloatRect getBounds() const override;
	sf::Vector2f getPos() const { return m_sprite.getPosition(); }
	void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }
	void drawArrows(sf::RenderWindow& window);
	std::vector<Arrow>& getArrowVector() { return m_arrowVector; }
	bool isDead() const override { return killFlag; }
	void dealDamage() override;
	EnemyType getType() const override { return EnemyType::Archer; }

private:
	void archerAnimations(sf::Vector2f playerPos);
	void fillFrames();
	void shootArrow(sf::Vector2f targetPos, sf::Vector2f pos);
	float calculateArrowRotation(sf::Vector2f targetPos, sf::Vector2f pos);
	bool checkPlayerLeftRight(sf::Vector2f playerPos);
	int frameDelay = 10;
	int frameCounter = 0;
	int currentFrame = 0;
	int frameWidth = 24;
	int frameHeight = 24;

	std::vector<sf::Vector2f> m_moveFrames;
	std::vector<sf::Vector2f> m_attackFrames;
	std::vector<sf::Vector2f> m_deathFrames;
	int m_currentMoveFrame = 0;
	int m_currentAttackFrame = 0;
	int m_currentDeathFrame = 0;
	bool m_isDead = false;
	bool killFlag = false;

	sf::Clock m_attackClock;
	float m_attackCooldown = 5.0f;
	bool isAttacking = false;

	//arrow for shooting vars
	std::vector<Arrow> m_arrowVector;
	const int MAX_ARROWS = 20;
	int m_arrowDelay = 0;
	const int maxArrowDelay = 10;
	const int arrowSpeed = 1000;
	const int arrowRotation = 0;
	bool shootArrowFlag = false;

};

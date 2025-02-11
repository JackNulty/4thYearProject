#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"
#include "Enemy.h"

class Heavy : public Enemy
{
public:
	Heavy(float x, float y);
	void update(float deltaTime) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos) override;
    void attack() override;
    bool canAttack() const { return m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown; }

private:

    void heavyAnimations();
    int frameDelay = 415;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;

    sf::Clock m_attackClock;
    float m_attackCooldown = 1.0f;
    std::vector<sf::Vector2f> m_attackFrames;
    int m_currentAttackFrame;
    void fillAttackFrames();

    bool isAttacking = false;
};


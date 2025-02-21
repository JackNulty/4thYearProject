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
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
    void attack(sf::Vector2f playerPos) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPos() const { return m_sprite.getPosition(); }
    void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }
    bool canAttack() const { return m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown; }
    void dealDamage();
    bool isDead() const { return m_isDead; }

private:

    void heavyAnimations();
    int frameDelay = 415;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;

    int m_health = 5;
    bool m_isDead = false;
    bool takeDamage = false;
    std::vector<sf::Vector2f> m_damageFrames;
    int m_currentDamageFrame;

    sf::Clock m_attackClock;
    float m_attackCooldown = 1.0f;
    std::vector<sf::Vector2f> m_attackFrames;
    int m_currentAttackFrame;
    void fillAttackFrames();

    bool isAttacking = false;
};


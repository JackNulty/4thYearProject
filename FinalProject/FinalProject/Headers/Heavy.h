#pragma once
#include "globals.h"
#include "EnemyBehavioursEnum.h"
#include "EnemyBehaviours.h"
#include "Enemy.h"

class Heavy : public Enemy
{
public:
	Heavy(float x, float y);
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
    void attack(sf::Vector2f playerPos) override;
    sf::FloatRect getBounds() const override;
    sf::Vector2f getPos() const { return m_sprite.getPosition(); }
    void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }
    bool canAttack() const { return m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown; }
    void dealDamage() override;
    bool isDead() const override { return m_killFlag; }
    EnemyType getType() const override { return EnemyType::Heavy; }

private:

    void heavyAnimations(sf::Vector2f playerPos);
    int frameDelay = 415;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;

    int m_health = 5;
    bool m_isDead = false;
    bool m_killFlag = false;
    bool takeDamage = false;
    std::vector<sf::Vector2f> m_damageFrames;
    int m_currentDamageFrame;

	PlayerPosition checkPLayerPosition(sf::Vector2f playerPos);

    sf::Clock m_attackClock;
    float m_attackCooldown = 1.0f;
    std::vector<sf::Vector2f> m_attackFramesLR;
	std::vector<sf::Vector2f> m_attackFramesUp;
	std::vector<sf::Vector2f> m_attackFramesDown;
	std::vector<sf::Vector2f> m_currentAttackFrameVector;
    std::vector<sf::Vector2f> m_deathFrames;
    int m_currentAttackFrame;
    int m_currentDeathFrame;
    void fillAttackFrames();

    bool isAttacking = false;
};


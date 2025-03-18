#pragma once
#include "globals.h"
#include "Enemy.h"

class Grunt : public Enemy {
public:
    Grunt(float x, float y);
    void update(float deltaTime, sf::Vector2f playerPos) override;
    void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
    void attack(sf::Vector2f playerPos) override;
	sf::FloatRect getBounds() const override;
    sf::Vector2f getPos() const { return m_sprite.getPosition(); }
    void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }
    void dealDamage() override;
    bool isDead() const override { return m_killFlag; }
    EnemyType getType() const override { return EnemyType::Grunt; }

private:
    void gruntAnimations();
    void fillFrames();
    int frameDelay = 315;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;
    bool m_isDead = false;
    bool m_killFlag = false;
    std::vector<sf::Vector2f> m_deathFrames;
    int m_currentDeathFrame = 0;
};


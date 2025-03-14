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
    bool isDead() const override { return m_isDead; }

private:
    void gruntAnimations();
    int frameDelay = 315;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;
    bool m_isDead = false;
};


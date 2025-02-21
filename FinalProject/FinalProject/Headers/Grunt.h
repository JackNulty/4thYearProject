#pragma once
#include "globals.h"
#include "Enemy.h"

class Grunt : public Enemy {
public:
    Grunt(float x, float y);
    void update(float deltaTime) override;
    void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
    void attack(sf::Vector2f playerPos) override;
	sf::FloatRect getBounds() const override;
    sf::Vector2f getPos() const { return m_sprite.getPosition(); }
    void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }

private:
    void gruntAnimations();
    int frameDelay = 315;
    int frameCounter = 0;
    int currentFrame = 0;
    int frameWidth = 32;
    int frameHeight = 32;
};


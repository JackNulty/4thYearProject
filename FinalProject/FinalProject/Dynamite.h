
#pragma once
#include "globals.h"
#include "Weapon.h"
#include "ResourceManager.h"

class Dynamite : public Weapon {
public:
    Dynamite();

    void update(float deltaTime, sf::Vector2f playerPos) override;
    void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::Vector2f mousePos, sf::View& cameraView) override;
    void render(sf::RenderWindow& window) override;
    void fire(sf::Vector2f playerPos, sf::Vector2f mousePos) override;
    sf::Sprite getSprite() override;
    void setActive(bool active) override { isActive = active; }
    void reset() override;
	bool getAttackFlag() { return showExplosion; }

    sf::CircleShape m_explosionCircle;

private:

    sf::Sprite m_dynamiteSprite;
	sf::Sprite m_dynamiteIcon;
    
    float explosionRadius = 0.f;
    float maxExplosionRadius = 100.f;

    sf::Vector2f velocity;

    float explosionTimer = 0.f;
    const float timeBeforeExplode = 2.f;
	bool hasExploded = false;

    bool showExplosion = false;
	bool isThrown = false;
};

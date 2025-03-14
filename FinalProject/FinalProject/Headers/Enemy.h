#pragma once
#include "globals.h"
#include "Behaviour.h"
#include "PlayerPosition.h"

class Enemy {
public:
    Enemy(float x, float y, float speed);
    virtual void update(float deltaTime, sf::Vector2f playerPos) = 0;
    virtual void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void attack(sf::Vector2f playerPos) = 0;
    virtual void dealDamage() = 0;
    virtual bool isDead() const = 0;

    virtual sf::FloatRect getBounds() const = 0;
    virtual sf::Vector2f getPos() const = 0;
    virtual void setPos(sf::Vector2f pos) = 0;
    void setBehaviour(std::unique_ptr<Behaviour> newBehaviour);
    sf::Vector2f m_velocity;

protected:
    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    float m_speed;
    float maxSpeed = 5.0f;
    float maxForce = 0.1f;
    std::unique_ptr<Behaviour> m_behaviour; 
};


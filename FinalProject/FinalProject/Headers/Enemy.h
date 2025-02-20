#pragma once
#include "globals.h"
#include "Behaviour.h"

class Enemy {
public:
    Enemy(float x, float y, float speed);
    virtual void update(float deltaTime) = 0;
    virtual void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) = 0;
    virtual void render(sf::RenderWindow& window);
    virtual void attack(sf::Vector2f playerPos) = 0;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPos() const;
    void setPos(sf::Vector2f pos);
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


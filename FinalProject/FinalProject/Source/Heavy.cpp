#include "Heavy.h"

Heavy::Heavy(float x, float y)
	: Enemy(x, y, 2.0f)
{
	if (!heavyTexture.loadFromFile("ASSETS/Enemies/Orc_Chief.png")) {
		std::cerr << "Error: Failed to load texture!" << std::endl;
	}
	m_sprite.setTexture(heavyTexture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(2, 2);
}

void Heavy::update(float deltaTime)
{
	heavyAnimations();
}

void Heavy::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
    if (m_behaviour) m_behaviour->update(*this, playerPos);

    m_velocity += m_acceleration;
    if (std::hypot(m_velocity.x, m_velocity.y) > maxSpeed) {
        m_velocity = (m_velocity / std::hypot(m_velocity.x, m_velocity.y)) * maxSpeed;
    }

    m_sprite.move(m_velocity);
    m_acceleration = { 0.0f, 0.0f };
}

void Heavy::heavyAnimations()
{
	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame = (currentFrame + 1) % 6;
		m_sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 96, frameWidth, frameHeight));
	}
}

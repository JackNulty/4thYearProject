#include "Archer.h"

Archer::Archer(float x, float y)
	: Enemy(x, y, 2.0f)
{
	if(!m_texture.loadFromFile("Assets/Enemies/Archer.png"))
	{
		std::cout << "Error loading Archer texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(2, 2);
}

void Archer::update(float deltaTime)
{
	archerAnimations();
}

void Archer::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (m_behaviour) m_behaviour->update(*this, playerPos);

	m_velocity += m_acceleration;
	if (std::hypot(m_velocity.x, m_velocity.y) > maxSpeed) {
		m_velocity = (m_velocity / std::hypot(m_velocity.x, m_velocity.y)) * maxSpeed;
	}

	m_sprite.move(m_velocity);
	m_acceleration = { 0.0f, 0.0f };

}

void Archer::attack()
{
}

void Archer::archerAnimations()
{
	frameCounter++;
	if (frameCounter >= frameDelay) {
		frameCounter = 0;
		currentFrame = (currentFrame + 1) % 6;
		m_sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 96, frameWidth, frameHeight));
	}
}

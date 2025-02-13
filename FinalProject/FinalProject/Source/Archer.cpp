#include "Archer.h"

Archer::Archer(float x, float y)
	: Enemy(x, y, 2.0f)
{
	if(!m_texture.loadFromFile("Assets/Enemies/Archer.png"))
	{
		std::cout << "Error loading Archer texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 16, 23));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(2, 2);
	fillFrames();
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
		m_currentMoveFrame = (m_currentMoveFrame + 1) % m_moveFrames.size();
		sf::Vector2f frame = m_moveFrames[m_currentMoveFrame];
		m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
	}
}

void Archer::fillFrames()
{
	m_moveFrames.push_back(sf::Vector2f(14, 162));
	m_moveFrames.push_back(sf::Vector2f(62, 162));
	m_moveFrames.push_back(sf::Vector2f(110, 162));
	m_moveFrames.push_back(sf::Vector2f(158, 162));
	m_moveFrames.push_back(sf::Vector2f(206, 162));
	m_moveFrames.push_back(sf::Vector2f(254, 162));
}

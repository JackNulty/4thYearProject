#include "Archer.h"

Archer::Archer(float x, float y)
	: Enemy(x, y, 2.0f)
{
	if (!m_texture.loadFromFile("Assets/Enemies/Archer.png"))
	{
		std::cout << "Error loading Archer texture" << std::endl;
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_sprite.setScale(2, 2);
	fillFrames();
}

void Archer::update(float deltaTime)
{

}

void Archer::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView)
{
	if (m_behaviour) m_behaviour->update(*this, playerPos);
	archerAnimations(playerPos);
	if (checkPlayerLeftRight(playerPos))
	{
		m_sprite.setScale(-2, 2);
	}
	else
	{
		m_sprite.setScale(2, 2);
	}
	m_velocity += m_acceleration;
	if (std::hypot(m_velocity.x, m_velocity.y) > maxSpeed) {
		m_velocity = (m_velocity / std::hypot(m_velocity.x, m_velocity.y)) * maxSpeed;
	}

	m_sprite.move(m_velocity);
	m_acceleration = { 0.0f, 0.0f };
	for (auto arrow = m_arrowVector.begin(); arrow != m_arrowVector.end();)
	{
		arrow->fixedUpdate(deltaTime);
		if (arrow->checkBounds(cameraView))
		{
			arrow = m_arrowVector.erase(arrow);
		}
		else {
			++arrow;
		}
	}
}

void Archer::attack(sf::Vector2f playerPos)
{
	if (canAttack())
	{
		isAttacking = true;
		m_attackClock.restart();
	}
}

void Archer::drawArrows(sf::RenderWindow& window)
{
	for (auto arrow : m_arrowVector)
	{
		arrow.render(window);
	}
}

void Archer::dealDamage()
{
	isDead = true;
}

void Archer::archerAnimations(sf::Vector2f playerPos)
{
	frameCounter++;
	if (!isAttacking)
	{
		if (frameCounter >= frameDelay) {
			frameCounter = 0;
			m_currentMoveFrame = (m_currentMoveFrame + 1) % m_moveFrames.size();
			sf::Vector2f frame = m_moveFrames[m_currentMoveFrame];
			m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
		}
	}
	else if (isDead)
	{
		if (frameCounter >= frameDelay) {
			frameCounter = 0;
			m_currentDeathFrame = (m_currentDeathFrame + 1) % m_deathFrames.size();
			sf::Vector2f frame = m_deathFrames[m_currentDeathFrame];
			m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
			if (m_currentDeathFrame == m_deathFrames.size() - 1)
			{
				killFlag = true;
			}
		}
	}
	else {
		if (frameCounter >= frameDelay) {
			frameCounter = 0;
			m_currentAttackFrame = (m_currentAttackFrame + 1) % m_attackFrames.size();
			sf::Vector2f frame = m_attackFrames[m_currentAttackFrame];
			m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
			if (m_currentAttackFrame == m_attackFrames.size() - 1)
			{
				isAttacking = false;
				shootArrow(playerPos, m_sprite.getPosition());
			}
		}
	}
}

void Archer::fillFrames()
{
	m_moveFrames.push_back(sf::Vector2f(14, 69));
	m_moveFrames.push_back(sf::Vector2f(62, 69));
	m_moveFrames.push_back(sf::Vector2f(110, 69));
	m_moveFrames.push_back(sf::Vector2f(158, 69));
	m_moveFrames.push_back(sf::Vector2f(206, 69));
	m_moveFrames.push_back(sf::Vector2f(254, 69));

	m_attackFrames.push_back(sf::Vector2f(18, 358));
	m_attackFrames.push_back(sf::Vector2f(64, 358));
	m_attackFrames.push_back(sf::Vector2f(111, 358));
	m_attackFrames.push_back(sf::Vector2f(160, 358));
	m_attackFrames.push_back(sf::Vector2f(208, 358));
	m_attackFrames.push_back(sf::Vector2f(256, 358));

	m_deathFrames.push_back(sf::Vector2f(16, 453));
	m_deathFrames.push_back(sf::Vector2f(66, 453));
	m_deathFrames.push_back(sf::Vector2f(114, 453));
	m_deathFrames.push_back(sf::Vector2f(162, 453));
}

void Archer::shootArrow(sf::Vector2f targetPos, sf::Vector2f pos)
{
	sf::Vector2f direction = targetPos - pos;
	float magnitude = getMagnitude(direction);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	if (m_arrowVector.size() < MAX_ARROWS)
	{
		m_arrowVector.emplace_back(pos, arrowSpeed, direction, calculateArrowRotation(targetPos, pos));
	}
	else
	{
		m_arrowVector.erase(m_arrowVector.begin());
		m_arrowVector.emplace_back(pos, arrowSpeed, direction, calculateArrowRotation(targetPos, pos));
	}
}

float Archer::calculateArrowRotation(sf::Vector2f targetPos, sf::Vector2f pos)
{
	sf::Vector2f direction = targetPos - pos;
	float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (magnitude != 0)
	{
		direction /= magnitude;
	}
	float angle = std::atan2(direction.y, direction.x) * 180 / PI;
	return angle + 270;
}

bool Archer::checkPlayerLeftRight(sf::Vector2f playerPos)
{
	// Calculate the distance between the player and the archer
	float distance = std::abs(playerPos.x - m_sprite.getPosition().x);

	// Check if the player is to the left or right of the archer
	if (playerPos.x < m_sprite.getPosition().x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

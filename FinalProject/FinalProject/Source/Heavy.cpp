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
	m_sprite.setScale(3, 3);
	fillAttackFrames();
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

void Heavy::attack(sf::Vector2f playerPos)
{
    if(canAttack())
	{
		isAttacking = true;
		m_attackClock.restart();
	}
}

void Heavy::dealDamage()
{
    m_health--;
    if (m_health <= 0) {
		m_isDead = true;
	}
    else {
        takeDamage = true;
    }
}

void Heavy::heavyAnimations()
{
    frameCounter++;
    if (!isAttacking)
    {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % 6;
            m_sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 96, frameWidth, frameHeight));
        }
    }
    else if (takeDamage)
    {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            m_currentDamageFrame = (m_currentDamageFrame + 1) % m_damageFrames.size();
            sf::Vector2f frame = m_damageFrames[m_currentDamageFrame];
            m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
            if (m_currentAttackFrame == 0) {
                takeDamage = false;
            }
        }
	}
    else
    {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            m_currentAttackFrame = (m_currentAttackFrame + 1) % m_attackFrames.size();
            sf::Vector2f frame = m_attackFrames[m_currentAttackFrame];
            m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
            if (m_currentAttackFrame == 0) {
                isAttacking = false;
            }
        }
    }
}

void Heavy::fillAttackFrames()
{
	m_attackFrames.push_back(sf::Vector2f(18, 209));
	m_attackFrames.push_back(sf::Vector2f(83, 209));
	m_attackFrames.push_back(sf::Vector2f(149, 209));
	m_attackFrames.push_back(sf::Vector2f(213, 209));
	m_attackFrames.push_back(sf::Vector2f(277, 209));
	m_attackFrames.push_back(sf::Vector2f(341, 209));	
	m_attackFrames.push_back(sf::Vector2f(405, 209));
	m_attackFrames.push_back(sf::Vector2f(469, 209));

    m_damageFrames.push_back(sf::Vector2f(5, 418));
    m_damageFrames.push_back(sf::Vector2f(37, 418));
    m_damageFrames.push_back(sf::Vector2f(69, 418));
    m_damageFrames.push_back(sf::Vector2f(101, 418));
}	

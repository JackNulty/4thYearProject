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

void Heavy::update(float deltaTime, sf::Vector2f playerPos)
{
	heavyAnimations(playerPos);
}

void Heavy::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView)
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
        PlayerPosition playerDirection = checkPLayerPosition(playerPos);

        switch (playerDirection)
        {
        case PlayerPosition::Left:
            m_sprite.setScale(-3, 3);
			m_currentAttackFrameVector = m_attackFramesLR;
            break;
        case PlayerPosition::Right:
            m_sprite.setScale(3, 3);
			m_currentAttackFrameVector = m_attackFramesLR;
            break;
        case PlayerPosition::Above:
            m_sprite.setScale(3, 3);
			m_currentAttackFrameVector = m_attackFramesUp;
            break;
        case PlayerPosition::Below:
            m_sprite.setScale(3, 3);
			m_currentAttackFrameVector = m_attackFramesDown;
            break;
        }
	}
}

sf::FloatRect Heavy::getBounds() const
{
	return m_sprite.getGlobalBounds();
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

void Heavy::heavyAnimations(sf::Vector2f playerPos)
{
    frameCounter++;
    if (!isAttacking)
    {
        PlayerPosition playerDirection = checkPLayerPosition(playerPos);
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % 6;

            int textureY = 128;

            switch (playerDirection) {
            case PlayerPosition::Left:
                m_sprite.setScale(-3, 3);
                break;
            case PlayerPosition::Right:
                m_sprite.setScale(3, 3);
                break;
            case PlayerPosition::Above:
                textureY = 66;  
                break;
            case PlayerPosition::Below:
                textureY = 96;  
                break;
            }

            m_sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, textureY, frameWidth, frameHeight));
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
    else if(m_isDead)
	{
		if (frameCounter >= frameDelay) {
			frameCounter = 0;
			m_sprite.setTextureRect(sf::IntRect(m_deathFrames[m_currentDeathFrame].x, m_deathFrames[m_currentDeathFrame].y, frameWidth, frameHeight));
			m_currentDeathFrame++;
			if (m_currentDeathFrame >= m_deathFrames.size()) {
				m_killFlag = true;
			}
		}
	}
    else
    {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            m_currentAttackFrame = (m_currentAttackFrame + 1) % m_attackFramesLR.size();
            sf::Vector2f frame = m_currentAttackFrameVector[m_currentAttackFrame];
            m_sprite.setTextureRect(sf::IntRect(frame.x, frame.y, frameWidth, frameHeight));
            if (m_currentAttackFrame == 0) {
                isAttacking = false;
            }
        }
    }
}

PlayerPosition Heavy::checkPLayerPosition(sf::Vector2f playerPos)
{
    sf::Vector2f heavyPos = m_sprite.getPosition();

    float xDifference = playerPos.x - heavyPos.x;
    float yDifference = playerPos.y - heavyPos.y;

    if (std::abs(xDifference) > std::abs(yDifference)) {
        // Player is more to the left or right
        if (xDifference < 0)
            return PlayerPosition::Left;
        else
            return PlayerPosition::Right;
    }
    else {
        // Player is more above or below
        if (xDifference < 0)
            return PlayerPosition::Above;
        else
            return PlayerPosition::Below;
    }
}

void Heavy::fillAttackFrames()
{
	m_attackFramesLR.push_back(sf::Vector2f(18, 275));
	m_attackFramesLR.push_back(sf::Vector2f(83, 275));
	m_attackFramesLR.push_back(sf::Vector2f(149, 275));
	m_attackFramesLR.push_back(sf::Vector2f(213, 275));
	m_attackFramesLR.push_back(sf::Vector2f(277, 275));
	m_attackFramesLR.push_back(sf::Vector2f(341, 275));
	m_attackFramesLR.push_back(sf::Vector2f(405, 275));
	m_attackFramesLR.push_back(sf::Vector2f(469, 275));

	m_attackFramesUp.push_back(sf::Vector2f(18, 209));
	m_attackFramesUp.push_back(sf::Vector2f(83, 209));
	m_attackFramesUp.push_back(sf::Vector2f(149, 209));
	m_attackFramesUp.push_back(sf::Vector2f(213, 209));
	m_attackFramesUp.push_back(sf::Vector2f(277, 209));
	m_attackFramesUp.push_back(sf::Vector2f(341, 209));
	m_attackFramesUp.push_back(sf::Vector2f(405, 209));
	m_attackFramesUp.push_back(sf::Vector2f(469, 209));

	m_attackFramesDown.push_back(sf::Vector2f(18, 337));
	m_attackFramesDown.push_back(sf::Vector2f(83, 337));
	m_attackFramesDown.push_back(sf::Vector2f(149, 337));
	m_attackFramesDown.push_back(sf::Vector2f(213, 337));
	m_attackFramesDown.push_back(sf::Vector2f(277, 337));
	m_attackFramesDown.push_back(sf::Vector2f(341, 337));
	m_attackFramesDown.push_back(sf::Vector2f(405, 337));  
	m_attackFramesDown.push_back(sf::Vector2f(469, 337));

    m_damageFrames.push_back(sf::Vector2f(5, 418));
    m_damageFrames.push_back(sf::Vector2f(37, 418));
    m_damageFrames.push_back(sf::Vector2f(69, 418));
    m_damageFrames.push_back(sf::Vector2f(101, 418));

    m_deathFrames.push_back(sf::Vector2f(5, 386));
    m_deathFrames.push_back(sf::Vector2f(39, 386));
    m_deathFrames.push_back(sf::Vector2f(71, 386));
    m_deathFrames.push_back(sf::Vector2f(102, 386));
}	

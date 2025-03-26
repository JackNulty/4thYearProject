#include "Thief.h"

Thief::Thief(float x, float y)
	:Enemy(x, y, 2.0f)
{
	if (!thiefTexture.loadFromFile("ASSETS/Enemies/Goblin_Thief.png")) {
		std::cout << "Error: Failed to load texture!" << std::endl;
	}
	m_thiefSprite.setTexture(thiefTexture);
	m_thiefSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
	m_thiefSprite.setOrigin(m_thiefSprite.getGlobalBounds().width / 2, m_thiefSprite.getGlobalBounds().height / 2);
	m_thiefSprite.setScale(2, 2);
	fillFrames();
}

void Thief::update(float deltaTime, sf::Vector2f playerPos)
{
	thiefAnimations(playerPos);
}

void Thief::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView)
{
	if (m_behaviour) m_behaviour->update(*this, playerPos);

	m_velocity += m_acceleration;
	if (std::hypot(m_velocity.x, m_velocity.y) > maxSpeed) {
		m_velocity = (m_velocity / std::hypot(m_velocity.x, m_velocity.y)) * maxSpeed;
	}

	m_thiefSprite.move(m_velocity);
	m_acceleration = { 0.0f, 0.0f };

}

void Thief::attack(sf::Vector2f playerPos)
{
}

sf::FloatRect Thief::getBounds() const
{
	return m_thiefSprite.getGlobalBounds();
}

void Thief::dealDamage()
{
	m_isDead = true;
}

void Thief::thiefAnimations(sf::Vector2f playerPos)
{
}

void Thief::fillFrames()
{
	//fill frames walk down
	m_frames.push_back(sf::IntRect(9, 102, 18, 18));
	m_frames.push_back(sf::IntRect(41, 103, 18, 18));
	m_frames.push_back(sf::IntRect(73, 104, 18, 18));
	m_frames.push_back(sf::IntRect(105, 102, 18, 18));
	m_frames.push_back(sf::IntRect(137, 103, 18, 18));
	m_frames.push_back(sf::IntRect(169, 104, 18, 18));

	//fill frames walk left + right
	m_framesLR.push_back(sf::IntRect(10, 134, 18, 18));
	m_framesLR.push_back(sf::IntRect(42, 135, 18, 18));
	m_framesLR.push_back(sf::IntRect(74, 136, 18, 18));
	m_framesLR.push_back(sf::IntRect(106, 134, 18, 18));
	m_framesLR.push_back(sf::IntRect(138, 135, 18, 18));
	m_framesLR.push_back(sf::IntRect(170, 136, 18, 18));

	//fill frames walk up
	m_framesDown.push_back(sf::IntRect(9, 166, 18, 18));
	m_framesDown.push_back(sf::IntRect(41, 167, 18, 18));
	m_framesDown.push_back(sf::IntRect(73, 168, 18, 18));
	m_framesDown.push_back(sf::IntRect(105, 166, 18, 18));
	m_framesDown.push_back(sf::IntRect(137, 167, 18, 18));
	m_framesDown.push_back(sf::IntRect(169, 168, 18, 18));

	//fill frames attack down
	m_attackFramesDown.push_back(sf::IntRect(9, 198, 18, 18));
	m_attackFramesDown.push_back(sf::IntRect(37, 200, 18, 18));
	m_attackFramesDown.push_back(sf::IntRect(66, 201, 28, 23));
	m_attackFramesDown.push_back(sf::IntRect(105, 200, 21, 22));
	m_attackFramesDown.push_back(sf::IntRect(137, 199, 18, 18));
	m_attackFramesDown.push_back(sf::IntRect(169, 200, 18, 18));

	//fill frames attack left + right
	m_attackFramesLR.push_back(sf::IntRect(10, 232, 18, 18));
	m_attackFramesLR.push_back(sf::IntRect(42, 233, 20, 18));
	m_attackFramesLR.push_back(sf::IntRect(68, 233, 28, 19));
	m_attackFramesLR.push_back(sf::IntRect(97, 232, 27, 20));
	m_attackFramesLR.push_back(sf::IntRect(137, 232, 18, 18));
	m_attackFramesLR.push_back(sf::IntRect(170, 232, 18, 18));

	//fill frames attack up
	m_attackFramesUp.push_back(sf::IntRect(9, 262, 18, 18));
	m_attackFramesUp.push_back(sf::IntRect(41, 264, 22, 18));
	m_attackFramesUp.push_back(sf::IntRect(66, 262, 28, 18));
	m_attackFramesUp.push_back(sf::IntRect(99, 264, 20, 20));
	m_attackFramesUp.push_back(sf::IntRect(137, 264, 18, 18));
	m_attackFramesUp.push_back(sf::IntRect(169, 264, 18, 18));

	//fill frames death
	m_deathFrames.push_back(sf::IntRect(10, 296, 18, 18));
	m_deathFrames.push_back(sf::IntRect(42, 296, 18, 18));
	m_deathFrames.push_back(sf::IntRect(74, 296, 18, 18));
	m_deathFrames.push_back(sf::IntRect(106, 296, 20, 18));
}


PlayerPosition Thief::checkPlayerPosition(sf::Vector2f playerPos)
{
	sf::Vector2f thiefPos = m_sprite.getPosition();

	float xDifference = playerPos.x - thiefPos.x;
	float yDifference = playerPos.y - thiefPos.y;

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

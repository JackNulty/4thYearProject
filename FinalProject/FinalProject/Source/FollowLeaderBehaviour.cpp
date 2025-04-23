#include "FollowLeaderBehaviour.h"

void FollowLeaderBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    if (m_leader.expired() || m_leader.lock().get() == &enemy) return;
	// go towards the leader with small offset
	sf::Vector2f direction = m_leader.lock()->getPos() - enemy.getPos();
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 25)
	{
		direction /= length;
		enemy.m_velocity += direction * 0.3f;
	}
}

std::unique_ptr<Behaviour> FollowLeaderBehaviour::clone() const
{
	return std::make_unique<FollowLeaderBehaviour>(m_leader);
}

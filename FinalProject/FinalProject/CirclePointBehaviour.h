#pragma once
#include "globals.h"
#include "Behaviour.h"

class CirclePointBehaviour : public Behaviour {
public:
	CirclePointBehaviour(const sf::Vector2f& target) : m_target(target) {}
	void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
	void setTarget(const sf::Vector2f& target) { m_target = target; }
	std::unique_ptr<Behaviour> clone() const override;
private:
	sf::Vector2f m_target;
};
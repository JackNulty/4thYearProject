#pragma once
#include "globals.h"
#include "Behaviour.h"
#include "Enemy.h"

class FollowLeaderBehaviour : public Behaviour {
public:
    FollowLeaderBehaviour(std::weak_ptr<Enemy> leader) : m_leader(leader) {}
    void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
    std::unique_ptr<Behaviour> clone() const override;

private:
    std::weak_ptr<Enemy> m_leader;
};

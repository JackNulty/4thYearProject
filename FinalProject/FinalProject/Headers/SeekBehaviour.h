#pragma once
#include "globals.h"
#include "Behaviour.h"


class SeekBehaviour : public Behaviour {
public:
    void update(Enemy& enemy, const sf::Vector2f& playerPos) override;
    std::unique_ptr<Behaviour> clone() const override;
};
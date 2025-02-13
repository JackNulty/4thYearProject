#include "KeepDistance.h"
#include "Enemy.h"

void KeepDistance::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    // Calculate the direction from the enemy to the player
    sf::Vector2f dir = enemy.getPos() - playerPos;

    // Calculate the length of the direction vector
    float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    // Check if the enemy is too close to the player
    if (length < 200.0f && length != 0)
    {
        // Normalize the direction vector
        dir /= length;

        // Increase the enemies velocity in the direction away from the player
        enemy.m_velocity += dir * 0.5f;
    }
    // Check if the enemy is too far from the player
    else if (length > 200.0f)
    {
        // Normalize the direction vector
        dir /= length;

        // Decrease the enemies velocity in the direction towards the player
        enemy.m_velocity -= dir * 0.5f;
    }
    // If the enemy is at an optimal distance from the player
    else
    {
        // Slow down the enemies velocity
        enemy.m_velocity *= 0.9f;
    }
}

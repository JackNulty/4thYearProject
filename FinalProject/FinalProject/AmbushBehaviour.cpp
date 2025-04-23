#include "AmbushBehaviour.h"

void AmbushBehaviour::update(Enemy& enemy, const sf::Vector2f& playerPos)
{
    sf::Vector2i mouseScreenPos = sf::Mouse::getPosition(); // Get mouse pos
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(mouseScreenPos);

    sf::Vector2f playerToMouse = mousePos - playerPos;
    float length = std::sqrt(playerToMouse.x * playerToMouse.x + playerToMouse.y * playerToMouse.y);

    if (length > 0) {
        playerToMouse /= length;
        sf::Vector2f behindPlayerPos = playerPos - playerToMouse * 30.0f; 
        sf::Vector2f direction = behindPlayerPos - enemy.getPos();

        float enemyDist = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (enemyDist > 25) {
            direction /= enemyDist;
            enemy.m_velocity += direction * 0.5f; // Moves towards position behind the player
        }
    }
}

std::unique_ptr<Behaviour> AmbushBehaviour::clone() const
{
	return std::make_unique<AmbushBehaviour>(*this);
}

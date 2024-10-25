#include "Player.h"

Player::Player()
{
	playerShape.setSize(sf::Vector2f(30, 30));
	playerShape.setOrigin(playerShape.getSize().x / 2, playerShape.getSize().y / 2);
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setPosition(100, 100);
}

void Player::update(float deltaTime)
{
}

void Player::fixedUpdate(float deltaTime)
{
    playerMovement(deltaTime);
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(playerShape);
}

sf::Vector2f Player::getPos()
{
    return playerShape.getPosition();
}

void Player::playerMovement(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerShape.move(0, -speed * deltaTime);  //up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerShape.move(-speed * deltaTime, 0);  //left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerShape.move(0, speed * deltaTime);    //down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerShape.move(speed * deltaTime, 0);    //right
    }
}

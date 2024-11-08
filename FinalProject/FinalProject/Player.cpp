#include "Player.h"

Player::Player()
{
	playerShape.setSize(sf::Vector2f(30, 30));
	playerShape.setOrigin(playerShape.getSize().x / 2, playerShape.getSize().y / 2);
	playerShape.setFillColor(sf::Color::Green);
	playerShape.setPosition(100, 100);
}

void Player::update(float deltaTime, sf::Vector2f mousePos)
{
}

void Player::fixedUpdate(float deltaTime, sf::Vector2f mousePos)
{
    playerMovement(deltaTime);
    shootBullet(mousePos);
    // loop through the player bullets depending on size and if it goes out of the screen bounds then delete it
    for (auto bullet = bulletVector.begin(); bullet != bulletVector.end();)
    {
        bullet->update(deltaTime);
        if (bullet->checkBounds())
        {
            bullet = bulletVector.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(playerShape);
    for (Bullet& bullet : bulletVector)
    {
        bullet.draw(window);
    }
}

sf::Vector2f Player::getPos()
{
    return playerShape.getPosition();
}

std::vector<Bullet>& Player::getBullets()
{
    return bulletVector;
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

void Player::shootBullet(sf::Vector2f mousePos)
{
    bulletDelay++;
    if(bulletDelay >= maxBulletDelay)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f currentPos = getPos();

            sf::Vector2f direction = mousePos - currentPos;
            float mag = getMagnitude(direction);
            if (mag != 0)
            {
                direction /= mag;
            }

            if (bulletVector.size() < MAX_BULLETS)
            {
                bulletVector.emplace_back(currentPos, direction, 300);
            }
            else {
                bulletVector.erase(bulletVector.begin());
                bulletVector.emplace_back(currentPos, direction, 300);
            }
            bulletDelay = 0;
        }
    }
    
}

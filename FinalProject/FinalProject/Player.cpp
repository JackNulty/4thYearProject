#include "Player.h"

Player::Player()
{
	m_playerShape.setSize(sf::Vector2f(30, 30));
	m_playerShape.setOrigin(m_playerShape.getSize().x / 2, m_playerShape.getSize().y / 2);
	m_playerShape.setFillColor(sf::Color::Green);
	m_playerShape.setPosition(100, 100);
}

void Player::update(float deltaTime, sf::Vector2f mousePos)
{
}

void Player::fixedUpdate(float deltaTime, sf::Vector2f mousePos)
{
    playerMovement(deltaTime);
    shootBullet(mousePos);
    // loop through the player bullets depending on size and if it goes out of the screen bounds then delete it
    for (auto bullet = m_bulletVector.begin(); bullet != m_bulletVector.end();)
    {
        bullet->update(deltaTime);
        if (bullet->checkBounds())
        {
            bullet = m_bulletVector.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

void Player::render(sf::RenderWindow& window)
{
	window.draw(m_playerShape);
    for (Bullet& bullet : m_bulletVector)
    {
        bullet.draw(window);
    }
}

sf::Vector2f Player::getPos()
{
    return m_playerShape.getPosition();
}

std::vector<Bullet>& Player::getBullets()
{
    return m_bulletVector;
}

void Player::playerMovement(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_playerShape.move(0, -m_speed * deltaTime);  //up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_playerShape.move(-m_speed * deltaTime, 0);  //left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_playerShape.move(0, m_speed * deltaTime);    //down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_playerShape.move(m_speed * deltaTime, 0);    //right
    }
}

void Player::shootBullet(sf::Vector2f mousePos)
{
    m_bulletDelay++;
    if(m_bulletDelay >= maxBulletDelay)
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

            if (m_bulletVector.size() < MAX_BULLETS)
            {
                m_bulletVector.emplace_back(currentPos, direction, 600);
            }
            else {
                m_bulletVector.erase(m_bulletVector.begin());
                m_bulletVector.emplace_back(currentPos, direction, 600);
            }
            m_bulletDelay = 0;
        }
    }
    
}

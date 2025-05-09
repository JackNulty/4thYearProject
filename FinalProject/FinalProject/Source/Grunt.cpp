#include "Grunt.h"
#include "Bullet.h"

Grunt::Grunt(float x, float y)
: Enemy(x, y, 2.0f) 
{
    if (!gruntTexture.loadFromFile("ASSETS/Enemies/Skeleton.png")) {
        std::cerr << "Error: Failed to load texture!" << std::endl;
    }
    m_sprite.setTexture(gruntTexture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
    m_sprite.setScale(2, 2);
    fillFrames();
}

void Grunt::update(float deltaTime, sf::Vector2f playerPos) {
    gruntAnimations();
}

void Grunt::fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) {
    if (m_behaviour) m_behaviour->update(*this, playerPos);

    m_velocity += m_acceleration;
    if (std::hypot(m_velocity.x, m_velocity.y) > maxSpeed) {
        m_velocity = (m_velocity / std::hypot(m_velocity.x, m_velocity.y)) * maxSpeed;
    }

    m_sprite.move(m_velocity);
    m_acceleration = { 0.0f, 0.0f };
}

void Grunt::attack(sf::Vector2f playerPos)
{
}

sf::FloatRect Grunt::getBounds() const
{
    return m_sprite.getGlobalBounds();
}

void Grunt::dealDamage()
{
    m_isDead = true;
}

void Grunt::gruntAnimations() {
    frameCounter++;
    if (m_isDead)
    {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            m_sprite.setTextureRect(sf::IntRect(m_deathFrames[m_currentDeathFrame].x, m_deathFrames[m_currentDeathFrame].y, frameWidth, frameHeight));
            m_currentDeathFrame++;
            if (m_currentDeathFrame >= m_deathFrames.size()) {
                m_killFlag = true;
            }
        }
	}
    else {
        if (frameCounter >= frameDelay) {
            frameCounter = 0;
            currentFrame = (currentFrame + 1) % 6;
            m_sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 96, frameWidth, frameHeight));
        }
    }
}

void Grunt::fillFrames()
{
    for (int i = 0; i < 4; i++)
	{
		m_deathFrames.push_back(sf::Vector2f(i * frameWidth, 192));
	}
}

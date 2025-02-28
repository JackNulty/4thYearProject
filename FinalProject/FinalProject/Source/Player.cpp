#include "Player.h"

Player::Player()
{
    if(!m_playerTexture.loadFromFile("Assets/Player/Player_Idle_Run_Death_Anim.png"))
	{
		std::cout << "Error loading player texture" << std::endl;
	}
    m_playerSprite.setTexture(m_playerTexture);
    m_playerSprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
    m_playerSprite.setOrigin(m_playerSprite.getGlobalBounds().width / 2, m_playerSprite.getGlobalBounds().height / 2);
    m_playerSprite.setPosition(100, 100);
    m_playerSprite.setScale(2, 2);
    m_playerSprite.setRotation(0);
    if(!m_livesTexture.loadFromFile("Assets/UI/UI_Icons.png"))
    {
        std::cout << "Error loading player lives texture" << std::endl;
	}
	m_livesSprite.setTexture(m_livesTexture);
	m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	m_livesSprite.setPosition(10, 10);
	m_livesSprite.setScale(2, 2);
    m_livesSpriteHalf.setTexture(m_livesTexture);
    m_livesSpriteHalf.setTextureRect(sf::IntRect(16, 0, 16, 16));
    m_livesSpriteHalf.setPosition(40, 10);
    m_livesSpriteHalf.setScale(2, 2);
    m_livesSpriteEmpty.setTexture(m_livesTexture);
    m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
    m_livesSpriteEmpty.setPosition(70, 10);
    m_livesSpriteEmpty.setScale(2, 2);
    m_weaponInventory.addWeapon(std::make_unique<Bow>());
}

void Player::update(float deltaTime, sf::Vector2f mousePos, sf::View& cameraView)
{
    displayLives();
    sf::Vector2f viewTopLeft = cameraView.getCenter() - (cameraView.getSize() / 2.0f);
    m_livesSprite.setPosition(viewTopLeft.x + 20, viewTopLeft.y + 20);
    m_livesSpriteHalf.setPosition(viewTopLeft.x + 50, viewTopLeft.y + 20);   
    m_livesSpriteEmpty.setPosition(viewTopLeft.x + 80, viewTopLeft.y + 20);
    for(auto& weapon : m_weaponInventory.m_weapons)
    {
        weapon->update(deltaTime, getPos());
    }
    //m_bow.update(deltaTime, getPos());
}

void Player::fixedUpdate(float deltaTime, sf::Vector2f mousePos, sf::View& cameraView)
{
    playerMovement(deltaTime);
    shootBullet(mousePos);
    playerAnimations();
    for (auto& weapon : m_weaponInventory.m_weapons)
    {
        weapon->fixedUpdate(deltaTime, getPos(), mousePos, cameraView);
    }
    //m_bow.fixedUpdate(deltaTime, getPos(), mousePos, cameraView);
    // loop through the player bullets depending on size and if it goes out of the screen bounds then delete it
    for (auto bullet = m_bulletVector.begin(); bullet != m_bulletVector.end();)
    {
        bullet->update(deltaTime);
        if (bullet->checkBounds(cameraView))
        {
            bullet = m_bulletVector.erase(bullet);
        }
        else {
            ++bullet;
        }
    }
}

void Player::render(sf::RenderWindow& window, sf::View& cameraViewRef)
{
	window.draw(m_playerSprite);
    window.draw(m_livesSprite);
    window.draw(m_livesSpriteHalf);
    window.draw(m_livesSpriteEmpty);
    m_weaponInventory.render(window, cameraViewRef);
    for (auto& weapon : m_weaponInventory.m_weapons)
	{
		weapon->render(window);
	}
    //m_bow.render(window);
    for (Bullet& bullet : m_bulletVector)
    {
        bullet.draw(window);
    }
}

sf::Vector2f Player::getPos()
{
    return m_playerSprite.getPosition();
}

std::vector<Bullet>& Player::getBullets()
{
    return m_bulletVector;
}

sf::FloatRect Player::getBounds() const
{
    return m_playerSprite.getGlobalBounds();
}

int Player::getLives()
{
    return lives;
}

void Player::removeLife()
{
    lives--;
}

void Player::addLife()
{
    lives++;
}

void Player::playerMovement(float deltaTime)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_playerSprite.move(0, -m_speed * deltaTime);  //up
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_playerSprite.move(-m_speed * deltaTime, 0);  //left
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_playerSprite.move(0, m_speed * deltaTime);    //down
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_playerSprite.move(m_speed * deltaTime, 0);    //right
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
        ParticleManager& particleManager = ResourceManager::getParticleManager();
        std::shared_ptr<ParticleSystem> system = particleManager.addParticleSystem(
            "muzzle_flash", 50, m_playerSprite.getPosition());
        system->configure(200.f, 1.0f, 2.f, sf::Color::Red);
        std::cout << "Added new particle system: muzzle_flash\n";
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

void Player::playerAnimations()
{
    // player animations
    //run animation
    frameCounter++;

    // Check if enough frames have passed to update the animation
    if (frameCounter >= frameDelay)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            m_playerSprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 160, frameWidth, frameHeight));
            m_playerSprite.setScale(2.0f, 2.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            m_playerSprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 128, frameWidth, frameHeight));
            m_playerSprite.setScale(-2.0f, 2.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            m_playerSprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 96, frameWidth, frameHeight));
            m_playerSprite.setScale(2.0f, 2.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_playerSprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 128, frameWidth, frameHeight));
            m_playerSprite.setScale(2.0f, 2.0f);
        }
        else
        {
            // Idle animation: use the first row of sprites
            m_playerSprite.setTextureRect(sf::IntRect(frameWidth * currentFrame, 0, frameWidth, frameHeight));
            m_playerSprite.setScale(2.0f, 2.0f);
        }

        // Update the frame counter
        frameCounter = 0;
        currentFrame++;
        if (currentFrame >= 6)
        {
            currentFrame = 0; // Loop back to the first frame
        }
    }
}

void Player::displayLives()
{
    if (lives == 0)
    {
        m_livesSprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
        m_livesSpriteHalf.setTextureRect(sf::IntRect(32, 0, 16, 16));
        m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
    }
    else if (lives == 1)
    {
		m_livesSprite.setTextureRect(sf::IntRect(16, 0, 16, 16));
		m_livesSpriteHalf.setTextureRect(sf::IntRect(32, 0, 16, 16));
		m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
	}
	else if (lives == 2)
	{
		m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		m_livesSpriteHalf.setTextureRect(sf::IntRect(16, 0, 16, 16));
		m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
	}
    else if (lives == 3)
    {
        m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteHalf.setTextureRect(sf::IntRect(16, 0, 16, 16));
        m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
    }
    else if (lives == 4)
    {
        m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteHalf.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteEmpty.setTextureRect(sf::IntRect(32, 0, 16, 16));
    }
    else if (lives == 5)
    { 
        m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteHalf.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteEmpty.setTextureRect(sf::IntRect(16, 0, 16, 16));
    }
    else if (lives == 6)
    {
        m_livesSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteHalf.setTextureRect(sf::IntRect(0, 0, 16, 16));
        m_livesSpriteEmpty.setTextureRect(sf::IntRect(0, 0, 16, 16));
    }
}


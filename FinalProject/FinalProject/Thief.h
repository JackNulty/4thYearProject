#pragma once
#include "globals.h"
#include "Enemy.h"

class Thief : public Enemy
{
public:
	Thief(float x, float y);
	void update(float deltaTime, sf::Vector2f playerPos) override;
	void fixedUpdate(float deltaTime, sf::Vector2f playerPos, sf::View& cameraView) override;
	void attack(sf::Vector2f playerPos) override;
	sf::FloatRect getBounds() const override;
	void dealDamage() override;
	bool isDead() const override { return m_killFlag; }
	EnemyType getType() const override { return EnemyType::Thief; }
	sf::Vector2f getPos() const { return m_sprite.getPosition(); }
	void setPos(sf::Vector2f pos) { m_sprite.setPosition(pos); }

private:
	void thiefAnimations(sf::Vector2f playerPos);
	void fillFrames();
	PlayerPosition checkPlayerPosition(sf::Vector2f playerPos);

	sf::Sprite m_thiefSprite;

	bool m_isDead = false;
	bool m_killFlag = false;
	std::vector <sf::IntRect> m_frames;
	std::vector<sf::IntRect> m_framesDown;
	std::vector<sf::IntRect> m_framesLR;
	std::vector<sf::IntRect> m_deathFrames;
	std::vector<sf::IntRect> m_attackFramesDown;
	std::vector<sf::IntRect> m_attackFramesLR;
	std::vector<sf::IntRect> m_attackFramesUp;
	int m_currentDeathFrame = 0;
	int frameDelay = 315;
	int frameCounter = 0;
	int currentFrame = 0;
	int frameWidth = 32;
	int frameHeight = 32;

};


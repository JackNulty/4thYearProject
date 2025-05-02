#pragma once
#include "globals.h"
#include "Bullet.h"
#include "Bow.h"
#include "../Sword.h"
#include "../Shuriken.h"
#include "../Dynamite.h"
#include "../Boomerang.h"

#include "ResourceManager.h"
#include "Weapon.h"
#include "../WeaponInventory.h"
#include "../PlayerHitEffect.h"

class Player
{
public:
	Player();
	void update(float deltaTime, sf::Vector2f mousePos, sf::View& cameraViewRef );
	void fixedUpdate(float deltaTime, sf::Vector2f mousePos, sf::View& cameraViewRef);
	void render(sf::RenderWindow& window, sf::View& cameraViewRef);
	sf::Vector2f getPos(); //  get player position
	std::vector<Bullet>& getBullets(); // get container of bullets
	sf::FloatRect getBounds() const; // get bounds of player
	int getLives(); // get player lives
	void removeLife(); // remove player life
	void addLife(); // add player life
	bool isShaking = false; // check if screen is shaking
	float shakeDuration = 0.0f; // duration of shake
	float shakeTimer = 0.0f; // timer for shake
	float shakeMagnitude = 5.0f; // magnitude of shake

	Bow m_bow; // bow object
	WeaponInventory m_weaponInventory; // weapon inventory

private:

	//private functions
	void playerMovement(float deltaTime); // func for player movement
	void shootBullet(sf::Vector2f mousePos); // func for shooting bullet 
	void playerAnimations(); // func for player animations
	void displayLives(); // func for displaying player lives
	void handleWeaponSwitch(); // func for handling weapon switch
	void updateHitEffects(); // func for updating hit effects

	//private vars
	sf::Texture m_playerTexture; // player texture
	sf::Sprite m_playerSprite; // player sprite
	sf::RectangleShape m_playerShape; // shape of player (placeholder for texture)
	float m_speed = 300.0f; // player speed
	std::vector<Bullet> m_bulletVector; // container for bullets
	const int MAX_BULLETS = 20; // maxz number of bullets
	int m_bulletDelay = 0; // delay counter for bullets
	const int maxBulletDelay = 10; // max delay for each mouse click to shoot bullets
	const int frameDelay = 5; // delay for each frame of animation
	int frameCounter = 0; // counter for frame delay
	int currentFrame = 0; // current frame of animation
	const int frameWidth = 32; // width of each frame
	const int frameHeight = 32; // height of each frame
	int lives = 6; // player lives
	sf::Texture m_livesTexture; // texture for player lives
	sf::Sprite m_livesSprite; // sprite for player lives
	sf::Sprite m_livesSpriteHalf; // sprite for player lives
	sf::Sprite m_livesSpriteEmpty; // sprite for player lives
	float m_lifeLossCooldown = 0.0f; // cooldown for life loss
	std::vector<PlayerHitEffect> m_hitEffects; // vector of hit effects
};


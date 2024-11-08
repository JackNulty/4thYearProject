#include "Grunt.h"
#include "Bullet.h"

Grunt::Grunt(EnemyBehaviourTypes startBehaviour)
	: currentBehaviour(startBehaviour){
	gruntShape.setSize(sf::Vector2f(30, 30));
	gruntShape.setOrigin(gruntShape.getSize().x / 2, gruntShape.getSize().y / 2);
	gruntShape.setFillColor(sf::Color::Red);
	gruntShape.setPosition(500, 500);
	m_speed = 2;
}

void Grunt::update(float deltaTime)
{
}

void Grunt::fixedUpdate(float deltaTime, sf::Vector2f playerPos)
{
	if (currentBehaviour == EnemyBehaviourTypes::Seek)
	{
		sf::Vector2f steering = behaviours.calculateSeek(gruntShape.getPosition(), playerPos, velocity, maxSpeed);
		acceleration += steering;
	}

	// limit velocity to max speed
	velocity += acceleration;
	float velocityMagnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
	if (velocityMagnitude > maxSpeed)
	{
		velocity = (velocity / velocityMagnitude) * maxSpeed;
	}

	//update sprite
	gruntShape.move(velocity);
	gruntShape.setRotation(behaviours.calculateRotation(gruntShape.getPosition(), playerPos));

	// reset acceleration
	acceleration = { 0.0f, 0.0f };
}

void Grunt::render(sf::RenderWindow& window)
{
	window.draw(gruntShape);
}

sf::FloatRect Grunt::getBounds() const
{
	return gruntShape.getGlobalBounds();
}


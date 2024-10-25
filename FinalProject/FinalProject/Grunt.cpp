#include "Grunt.h"

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
		gruntShape.move(behaviours.calculateSeek(gruntShape.getPosition(), playerPos, m_speed));
	}
	gruntShape.setRotation(behaviours.calculateRotation(gruntShape.getPosition(), playerPos));
}

void Grunt::render(sf::RenderWindow& window)
{
	window.draw(gruntShape);
}

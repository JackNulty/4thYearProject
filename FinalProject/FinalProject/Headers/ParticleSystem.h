#pragma once
#include "globals.h"
#include <functional>

struct Particle
{
	sf::Vector2f velocity;
	sf::Time lifetime;
	sf::CircleShape shape;

	Particle(float radius, const sf::Color& colour);
};

enum class EmmissionMode
{
	Constant,
	Single
};

class ParticleSystem
{
public:
	ParticleSystem(size_t maxParticles, sf::Vector2f position, std::string id);
	void setEmitter(sf::Vector2f position);
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	void configure(float speed, float lifetime, float radius, const sf::Color& colour);
	bool isEmpty() const;
	int getParticleCount() const;
	void setEmissionMode(EmmissionMode mode) { m_emissionMode = mode; }

	void deactivate() { m_active = false; }
	bool isActive() const { return m_active; }

private:
	void emitParticles();
	std::vector<Particle> m_particles;
	size_t m_maxParticles;
	sf::Vector2f m_emitter;

	std::string m_id;

	float m_particleSpeed = 100.f;
	sf::Time m_particleLifetime = sf::seconds(2.f);
	float m_particleRadius = 5.f;
	sf::Color m_particleColour = sf::Color::White;

	bool m_active = true;
	EmmissionMode m_emissionMode = EmmissionMode::Single;
};

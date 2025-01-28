#pragma once
#include "globals.h"
#include "ParticleSystem.h"

class ParticleManager
{
public:
	// adds a particle system to the manager returns shared pointer to the particle system
	std::shared_ptr<ParticleSystem> addParticleSystem(const std::string& id, size_t maxParticles, sf::Vector2f position);

	// gets shared pointer to existing particle system using id
	std::shared_ptr<ParticleSystem> getParticleSystem(const std::string& id);

	bool hasParticleSystem(const std::string& id) const;

	void update(float deltaTime);
	void render(sf::RenderWindow& window);

private:
	std::map<std::string, std::shared_ptr<ParticleSystem>> m_particleSystems;
};


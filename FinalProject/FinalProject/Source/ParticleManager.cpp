#include "ParticleManager.h"

std::shared_ptr<ParticleSystem> ParticleManager::addParticleSystem(const std::string& id, size_t maxParticles, sf::Vector2f position)
{
	auto system = std::make_shared<ParticleSystem>(maxParticles, position);
	m_particleSystems[id] = system;
    return system;
}

std::shared_ptr<ParticleSystem> ParticleManager::getParticleSystem(const std::string& id)
{
	if (m_particleSystems.count(id))
	{
		return m_particleSystems[id];
	}
    return nullptr;
}

bool ParticleManager::hasParticleSystem(const std::string& id) const
{
	return m_particleSystems.find(id) != m_particleSystems.end();
}

void ParticleManager::update(float deltaTime)
{
    //std::cout << "Updating particle systems...\n";
    //std::cout << "Total systems: " << m_particleSystems.size() << "\n";

    for (auto iterator = m_particleSystems.begin(); iterator != m_particleSystems.end();)
    {
        //std::cout << "Updating system: " << iterator->first << "\n";
        iterator->second->update(deltaTime);

        if (iterator->second->isEmpty())
        {
            //std::cout << "Removing system: " << iterator->first << "\n";
            iterator = m_particleSystems.erase(iterator);
        }
        else
        {
            ++iterator;
        }
    }
}

void ParticleManager::render(sf::RenderWindow& window)
{
	// render each particle system in the map 
	for(auto& particleSystem : m_particleSystems)
	{
		particleSystem.second->render(window);
	}
}

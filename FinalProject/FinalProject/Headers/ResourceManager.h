#pragma once
#include "globals.h"
#include "ParticleManager.h"

class ResourceManager
{
public:
	// get singleton instance of particle manager
	static ParticleManager& getParticleManager();

private:
	// make default to prevent creation of default constructor
	ResourceManager() = default;
	~ResourceManager() = default;

	// delete copy constructor and assignment operator
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
};


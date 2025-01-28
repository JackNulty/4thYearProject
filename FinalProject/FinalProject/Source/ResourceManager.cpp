#include "ResourceManager.h"

ParticleManager& ResourceManager::getParticleManager()
{
    static ParticleManager particleManager;
    return particleManager;
}

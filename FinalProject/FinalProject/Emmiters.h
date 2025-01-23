#pragma once

#include "globals.h"
#include "ParticleSystem.h"

void arrowTrailEmitter(Particle& p);

inline void arrowTrailEmitter(Particle& p) {
    p.velocity = { 0, -50 };
    p.colour = sf::Color(255, 255, 255, 200);
    p.lifetime = 0.5f;
}
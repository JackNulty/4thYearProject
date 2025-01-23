#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(int maxParticles)
	: m_particles(maxParticles), m_vertices(sf::Quads, maxParticles * 4), m_texture(nullptr), m_blendMode(sf::BlendAlpha)
{
}

void ParticleSystem::update(float deltaTime)
{
	for (Particle& particle : m_particles)
	{
		if (particle.lifetime > 0)
		{
			particle.position += particle.velocity * deltaTime;
			particle.lifetime -= deltaTime;

			//update particle 
			float life = particle.lifetime / 1;
			sf::Color fadeColour = particle.colour;
			fadeColour.a = static_cast<sf::Uint8>(life * 255);

			//update vertices
			size_t index = &particle - &m_particles[0];
			for(int i = 0; i < 4; i++)
			{
				m_vertices[index * 4 + i].position = particle.position;
				m_vertices[index * 4 + i].color = fadeColour;
			}
		}
	}
}

void ParticleSystem::setTexture(sf::Texture& texture)
{
	this->m_texture = &texture;
}

void ParticleSystem::emitParticles(sf::Vector2f& position, std::function<void(Particle&)> init, int particleCount)
{
	for(Particle& particle : m_particles)
	{
		if(particle.lifetime <= 0 && particleCount > 0)
		{
			particle.position = position;
			particle.lifetime = 1;
			init(particle);
			
			//update vertices
			size_t index = &particle - &m_particles[0];
			for (int i = 0; i < 4; i++)
			{
				m_vertices[index * 4 + i].position = particle.position;
			}
			particleCount--;
		}
	}
}

void ParticleSystem::setBlendMode(sf::BlendMode blendMode)
{
	m_blendMode = blendMode;
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(m_texture)
	{
		states.texture = m_texture;
	}
	states.blendMode = m_blendMode;
	target.draw(m_vertices, states);

}


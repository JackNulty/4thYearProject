#include "ParticleSystem.h"

// particle contructor
Particle::Particle(float radius, const sf::Color& colour)
	: shape(radius) {
	shape.setFillColor(colour);
}

// particle system constructor
ParticleSystem::ParticleSystem(size_t maxParticles, sf::Vector2f position, std::string id)
	: m_maxParticles(maxParticles),
	m_emitter(position),
	m_id(id)
{
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

void ParticleSystem::update(float deltaTime)
{
	for (auto iterator = m_particles.begin(); iterator != m_particles.end();)
	{
		iterator->lifetime -= sf::seconds(deltaTime);

		if (iterator->lifetime <= sf::Time::Zero)
		{
			iterator = m_particles.erase(iterator);
		}
		else
		{
			iterator->shape.move(iterator->velocity * deltaTime);
			++iterator;
		}
	}

	static float emissionCooldown = 0.0f;
	emissionCooldown += deltaTime;

	if (emissionCooldown >= 0.02f) 
	{
		emitParticles();
		emissionCooldown = 0.0f;  // Reset cooldown
	}
	if (m_particles.empty())
	{
		m_active = false; // Deactivate the system when empty
		//std::cout << "Particle system is now empty and deactivated.\n";
	}
}

void ParticleSystem::render(sf::RenderWindow& window)
{
	for(Particle& particle : m_particles)
	{
		window.draw(particle.shape);
	}
}

void ParticleSystem::configure(float speed, float lifetime, float radius, const sf::Color& colour)
{
	m_particleSpeed = speed;
	m_particleLifetime = sf::seconds(lifetime);
	m_particleRadius = radius;
	m_particleColour = colour;
}

bool ParticleSystem::isEmpty() const
{
	//std::cout << "Checking if particle system is empty: " << m_particles.empty() << "\n";
	return m_particles.empty();
}

int ParticleSystem::getParticleCount() const
{
	return m_particles.size();
}

void ParticleSystem::emitParticles()
{
	if (!m_active) return;
	if (m_particles.empty()) // Emit only if the system is empty
    {
        for (size_t i = 0; i < m_maxParticles; ++i)
        {
            Particle particle(m_particleRadius, m_particleColour);
            particle.shape.setPosition(m_emitter);

			float angle; //= (std::rand() % 360) * PI / 180.0f;
			if (m_id == "grunt_hit")
			{ 
				angle = (std::rand() % 60 + 210) * PI / 180.0f;
				particle.velocity.x *= (std::rand() % 2 + 0.5f); // Varying spread
				particle.velocity.y *= (std::rand() % 2 + 0.5f);
				particle.velocity = { m_particleSpeed * std::cos(angle), m_particleSpeed * std::sin(angle) };
			}
			else if (m_id == "arrow_fired")
			{
				angle = 270 * PI / 180.0f;
				particle.velocity.x *= 0.1f; 
				particle.velocity = { m_particleSpeed * std::cos(angle), m_particleSpeed * std::sin(angle) };
			}
			else if (m_id == "dynamite_explosion")
			{
				angle = (std::rand() % 360) * PI / 180.0f;

				// random jitter
				float angleJitter = ((std::rand() % 2001) - 1000) / 1000.f * (10.f * PI / 180.f);
				angle += angleJitter;

				//variable speed
				float speedJitter = static_cast<float>((std::rand() % 70 + 60)) / 100.f;

				particle.velocity = {
					m_particleSpeed * speedJitter * std::cos(angle),
					m_particleSpeed * speedJitter * std::sin(angle)
				};
				particle.shape.setRadius(m_particleRadius * (0.7f + (std::rand() % 60) / 100.f));
			}
			else {
				angle = (std::rand() % 360) * PI / 180.0f;
				particle.velocity = { m_particleSpeed * std::cos(angle), m_particleSpeed * std::sin(angle) };
			}

            particle.lifetime = m_particleLifetime;

            m_particles.push_back(particle);
        }
    }
}

#pragma once
#include "globals.h"
#include <functional>

struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color colour;
	float lifetime;
};

class ParticleSystem : public sf::Drawable
{
public:

	ParticleSystem(int maxParticles);
	void update(float deltaTime);
	void setTexture(sf::Texture& texture);
	void emitParticles(sf::Vector2f& position, std::function<void(Particle&)> init, int particleCount);
	void setBlendMode(sf::BlendMode blendMode);

private:

	std::vector<Particle> m_particles;
	sf::Texture *m_texture;
	sf::BlendMode m_blendMode;
	sf::VertexArray m_vertices;

	// using draw rather than render to save on preformance to batch render particles 
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

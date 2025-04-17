#include "PlayerHitEffect.h"

PlayerHitEffect::PlayerHitEffect(sf::Texture& texture, sf::Vector2f position)
{
	if (!texture.loadFromFile("ASSETS/UI/heart.png"))
	{
		std::cout << "Error loading player hit effect texture" << std::endl;
	}
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    sprite.setScale(1.0f, 1.0f);
    sprite.setColor(sf::Color(255, 255, 255, 255));
}

void PlayerHitEffect::update()
{
    float time = clock.getElapsedTime().asSeconds() / duration;

    // shrink and fade out
    float scale = 1.0f - time;
    sprite.setScale(scale, scale);

    int alpha = static_cast<int>((1.0f - time) * 255);
    sf::Color col = sprite.getColor();
    col.a = alpha;
    sprite.setColor(col);

    // float upward
    sprite.move(0.f, -0.3f * time);
}

bool PlayerHitEffect::isFinished() const
{
	return clock.getElapsedTime().asSeconds() > duration;
}

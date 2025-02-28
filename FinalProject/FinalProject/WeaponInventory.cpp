#include "WeaponInventory.h"

WeaponInventory::WeaponInventory()
{
	m_hotbarBackground.setSize(sf::Vector2f(200, 50));
	m_hotbarBackground.setFillColor(sf::Color::Black);
	m_hotbarBackground.setOutlineColor(sf::Color::White);
	m_hotbarBackground.setOutlineThickness(2);
	m_hotbarBackground.setPosition(10, 10);
}

void WeaponInventory::addWeapon(std::unique_ptr<Weapon> weapon)
{
	m_weapons.push_back(std::move(weapon));
}

void WeaponInventory::nextWeapon()
{
	if(!m_weapons.empty())
	{
		selectedWeapon = (selectedWeapon + 1) % m_weapons.size();
	}
}

void WeaponInventory::previousWeapon()
{
	if(!m_weapons.empty())
	{
		selectedWeapon = (selectedWeapon - 1 + m_weapons.size()) % m_weapons.size();
	}
}

Weapon* WeaponInventory::getSelectedWeapon()
{
	return m_weapons[selectedWeapon].get();
}

void WeaponInventory::render(sf::RenderWindow& window, const sf::View& cameraView)
{
	sf::Vector2f viewCenter = cameraView.getCenter();
	sf::Vector2f viewSize = cameraView.getSize();

	float hotbarX = viewCenter.x - (viewSize.x / 2) + 50;  // 50px offset from left
	float hotbarY = viewCenter.y + (viewSize.y / 2) - 70;  // 70px offset from bottom
	m_hotbarBackground.setPosition(hotbarX, hotbarY);

	window.draw(m_hotbarBackground);
	for (int i = 0; i < m_weapons.size(); i++)
	{
		sf::Sprite weaponSprite = m_weapons[i]->getSprite();
		weaponSprite.setScale(2, 2);
		weaponSprite.setPosition(hotbarX + 10 + i * 60, hotbarY + 10);
		std::cout << weaponSprite.getPosition().x << " " << weaponSprite.getPosition().y << std::endl;
		window.draw(weaponSprite);
		if(i == selectedWeapon)
		{
			sf::RectangleShape highlight(sf::Vector2f(50, 50));
			highlight.setPosition(hotbarX + 10 + i * 60, hotbarY + 10);
			highlight.setOutlineThickness(3);
			highlight.setOutlineColor(sf::Color::Yellow);
			highlight.setFillColor(sf::Color::Transparent);
			window.draw(highlight);
		}
	}
}

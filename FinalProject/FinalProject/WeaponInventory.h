#pragma once
#include "globals.h"
#include "Weapon.h"
#include "Boomerang.h"

class WeaponInventory {
public:
	WeaponInventory();
	std::vector<std::unique_ptr<Weapon>> m_weapons;
	int selectedWeapon = 0;
	void addWeapon(std::unique_ptr<Weapon> weapon);
	void nextWeapon();
	void previousWeapon();
	Weapon* getSelectedWeapon();
	void render(sf::RenderWindow& window, const sf::View& cameraView);
private:
	sf::RectangleShape m_hotbarBackground;
	const int MAX_WEAPONS = 5;
	std::vector<sf::Sprite> m_hotbarSprites;


};

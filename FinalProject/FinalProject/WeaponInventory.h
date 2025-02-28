#pragma once
#include "globals.h"
#include "Weapon.h"

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
};

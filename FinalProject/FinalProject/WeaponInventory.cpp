#include "WeaponInventory.h"

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

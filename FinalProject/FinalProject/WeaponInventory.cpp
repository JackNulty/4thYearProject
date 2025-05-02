#include "WeaponInventory.h"

WeaponInventory::WeaponInventory()
{
	if (!uiFrameTexture.loadFromFile("ASSETS/UI/UI_Frames.png"))
	{
		std::cout << "Error: Failed to load texture!" << std::endl;
	}
	sf::IntRect slotRect = { 295, 7, 34, 34 };
	for (int i = 0; i < MAX_WEAPONS; i++) {
		sf::Sprite hotbarSprite(uiFrameTexture);
		hotbarSprite.setScale(2.0f, 2.0f);
		hotbarSprite.setTextureRect(slotRect);
		m_hotbarSprites.push_back(hotbarSprite);
	}
}

void WeaponInventory::addWeapon(std::unique_ptr<Weapon> weapon)
{
	if (m_weapons.size() >= MAX_WEAPONS)
	{
		return;
	}
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

	float hotbarX = viewCenter.x - (viewSize.x / 2) + 50;  
	float hotbarY = viewCenter.y + (viewSize.y / 2) - 70;  
	float slotSpacing = 80;

	for (size_t i = 0; i < m_hotbarSprites.size(); i++) {
		sf::Sprite& slot = m_hotbarSprites[i];

		// Position slots across the bottom of the screen
		slot.setPosition(hotbarX + (i * slotSpacing), hotbarY);
		window.draw(slot);

		// Draw the weapon in the center of the slot if available
        if (i < m_weapons.size()) {  
			sf::Sprite weaponSprite = m_weapons[i]->getSprite();  

			// Check if the weapon is a Boomerang and scale less as sprite is a bit bigger
			if (dynamic_cast<Boomerang*>(m_weapons[i].get())) {  
				weaponSprite.setScale(2.f, 2.f);  
			} else {  
				weaponSprite.setScale(3.f, 3.f);  
			}

			// Center the weapon sprite within the slot
			sf::FloatRect slotBounds = slot.getGlobalBounds();
			sf::FloatRect weaponBounds = weaponSprite.getGlobalBounds();
            float weaponX = slotBounds.left + (slotBounds.width / 2) - (weaponBounds.width / 2);
            float weaponY = slotBounds.top + (slotBounds.height / 2) - (weaponBounds.height / 2);
            weaponSprite.setPosition(weaponX, weaponY ); 

			window.draw(weaponSprite);
		}

		// Highlight selected slot
		if (i == selectedWeapon) {
			sf::RectangleShape highlight(sf::Vector2f(slot.getGlobalBounds().width, slot.getGlobalBounds().height));
			highlight.setPosition(slot.getPosition());
			highlight.setOutlineThickness(3);
			highlight.setOutlineColor(sf::Color::Red);
			highlight.setFillColor(sf::Color::Transparent);
			window.draw(highlight);
		}
	}
}

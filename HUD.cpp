#include "HUD.h"

// Constructor
HUD::HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player)
    : player(player)
{
    // Initialize HUD background
    background.setFillColor(sf::Color::Black); // background color is black
    background.setOutlineThickness(5);         //  outline thickness (5 pixels)
    background.setOutlineColor(sf::Color::Magenta); //  outline color to magenta

    // Initialize HUD text for health
    healthText.setFont(font);
    healthText.setCharacterSize(40);
    healthText.setFillColor(sf::Color::Green);

    // Initialize HUD text for ammo
    ammoText.setFont(font);
    ammoText.setCharacterSize(40);
    ammoText.setFillColor(sf::Color::Cyan);

    //initialise score
    scoreText.setFont(font);
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::Yellow);

    //initialise inventory weapon
    weaponText.setFont(font);
    weaponText.setCharacterSize(40);
    weaponText.setFillColor(sf::Color::White);

    //initialise health potion text
    healthPotionText.setFont(font);
    healthPotionText.setCharacterSize(40);
    healthPotionText.setFillColor(sf::Color::Red);

    // Set the initial position on the bottom of the screen
    updatePosition(windowSize);
}

// Update position of HUD to be at the bottom of the screen
void HUD::updatePosition(const sf::Vector2f& windowSize) {
    float hudHeight = windowSize.y / 10.0f; // Height of the HUD

    // Set the size and position of the background rectangle
    background.setSize(sf::Vector2f(windowSize.x + 300, hudHeight)); // Full width of the window
    background.setPosition(-200, windowSize.y - hudHeight - 20); // Position it at the bottom of the window

    // Set the position of HUD elements (e.g., healthText and ammoText)
    healthText.setPosition(-100, windowSize.y - hudHeight); // Adjust 
    ammoText.setPosition(200, windowSize.y - hudHeight ); // Adjust 
    scoreText.setPosition(500, windowSize.y - hudHeight); // Adjust 
    weaponText.setPosition(800, windowSize.y - hudHeight); // Adjust 
    healthPotionText.setPosition(1200, windowSize.y - hudHeight); // Adjust 
}

// Update HUD elements based on player status
void HUD::update()
{
    // Update health and ammo texts
    healthText.setString("Health: " + std::to_string((int)(player.getHealth())));
    ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
    scoreText.setString("Score: " + std::to_string(player.getScore()));
    Weapon* currentWeapon = player.getCurrentWeapon(); // Get the current weapon
    if (currentWeapon) {
        weaponText.setString("Weapon: " + currentWeapon->getName()); // Set weapon name
    } else {
        weaponText.setString("Weapon: None"); // No weapon equipped
    }
    healthPotionText.setString("Health potions: " + std::to_string(player.getHealthPotionCount()));

}

// Draw HUD on the screen
void HUD::draw(sf::RenderWindow& window)
{
    window.draw(background); // Draw the background rectangle first
    window.draw(healthText);
    window.draw(ammoText);
    window.draw(scoreText);
    window.draw(weaponText);
    window.draw(healthPotionText);
}

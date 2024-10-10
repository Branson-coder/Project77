#include "HUD.h"

// Constructor
HUD::HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player)
    : player(player)
{
    // Initialize HUD background
    background.setFillColor(sf::Color::Black); // Set background color to black

    // Initialize HUD text for health
    healthText.setFont(font);
    healthText.setCharacterSize(50);
    healthText.setFillColor(sf::Color::Red);

    // Initialize HUD text for ammo
    ammoText.setFont(font);
    ammoText.setCharacterSize(50);
    ammoText.setFillColor(sf::Color::Green);

    //initialise score
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Yellow);

    //initialise inventory weapon
    weaponText.setFont(font);
    weaponText.setCharacterSize(50);
    weaponText.setFillColor(sf::Color::White);



    // Set the initial position on the bottom of the screen
    updatePosition(windowSize);
}

// Update position of HUD to be at the bottom of the screen
void HUD::updatePosition(const sf::Vector2f& windowSize) {
    float hudHeight = windowSize.y / 10.0f; // Height of the HUD

    // Set the size and position of the background rectangle
    background.setSize(sf::Vector2f(windowSize.x, hudHeight)); // Full width of the window
    background.setPosition(-30, windowSize.y - hudHeight - 20); // Position it at the bottom of the window

    // Set the position of HUD elements (e.g., healthText and ammoText)
    healthText.setPosition(0, windowSize.y - hudHeight); // Adjust 
    ammoText.setPosition(350, windowSize.y - hudHeight ); // Adjust 
    scoreText.setPosition(700, windowSize.y - hudHeight); // Adjust 
    weaponText.setPosition(1000, windowSize.y - hudHeight); // Adjust 
}

// Update HUD elements based on player status
void HUD::update()
{
    // Update health and ammo texts
    healthText.setString("Health: " + std::to_string(player.getHealth()));
    ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
    scoreText.setString("Score: " + std::to_string(player.getScore()));
    Weapon* currentWeapon = player.getCurrentWeapon(); // Get the current weapon
    if (currentWeapon) {
        weaponText.setString("Weapon: " + currentWeapon->getName()); // Set weapon name
    } else {
        weaponText.setString("Weapon: None"); // No weapon equipped
    }

}

// Draw HUD on the screen
void HUD::draw(sf::RenderWindow& window)
{
    window.draw(background); // Draw the background rectangle first
    window.draw(healthText);
    window.draw(ammoText);
    window.draw(scoreText);
    window.draw(weaponText);
}

#include "HUD.h"

// Constructor
HUD::HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player)
    : player(player),
      font(font),
      showMessage(false),
      messageDuration(2),
      messageInterval(5),
      elapsedTime(0),
      messageIndex(0) {
  // Initialize HUD background
  background.setFillColor(sf::Color::Black);  // background color is black
  background.setOutlineThickness(5);          //  outline thickness (5 pixels)
  background.setOutlineColor(sf::Color::Magenta);  //  outline color to magenta

  backgroundRight.setFillColor(sf::Color::Black);  // background color is black
  backgroundRight.setOutlineThickness(5);  //  outline thickness (5 pixels)
  backgroundRight.setOutlineColor(
      sf::Color::Magenta);  //  outline color to magenta

  // Initialize HUD text for health
  healthText.setFont(font);
  healthText.setCharacterSize(40);
  healthText.setFillColor(sf::Color::Green);

  // Initialize HUD text for ammo
  ammoText.setFont(font);
  ammoText.setCharacterSize(40);
  ammoText.setFillColor(sf::Color::Cyan);

  // initialise score
  scoreText.setFont(font);
  scoreText.setCharacterSize(40);
  scoreText.setFillColor(sf::Color::Yellow);

  // initialise inventory weapon
  weaponText.setFont(font);
  weaponText.setCharacterSize(40);
  weaponText.setFillColor(sf::Color::White);

  // initialise health potion text
  healthPotionText.setFont(font);
  healthPotionText.setCharacterSize(40);
  healthPotionText.setFillColor(sf::Color::Red);

  tutorialText.setFont(font);
  tutorialText.setCharacterSize(30);
  tutorialText.setFillColor(sf::Color::White);

  messages = {"Nice shot!",      "Close one!",  "Well done!", "Keep it up!",
              "You're amazing!", "Great move!", "Keep going!"};

  // Set the initial position on the bottom of the screen
  updatePosition(windowSize);
}

// Update position of HUD to be at the bottom of the screen
void HUD::updatePosition(const sf::Vector2f& windowSize) {
  // HUD height
  float hudHeight = 100;             // Set the height of the HUD
  float backgroundRightWidth = 100;  // Width of the backgroundRight

  // Set the size and position of the background rectangle (HUD)
  background.setSize(
      sf::Vector2f(windowSize.x - 500, hudHeight));  // Full width of the window
  background.setPosition(0,
                         windowSize.y - hudHeight -
                             110);  // Position it at the bottom of the window

  // Set the position of HUD elements
  healthText.setPosition(10, windowSize.y - hudHeight - 85);
  ammoText.setPosition(230, windowSize.y - hudHeight - 85);
  scoreText.setPosition(430, windowSize.y - hudHeight - 85);
  weaponText.setPosition(710, windowSize.y - hudHeight - 85);
  healthPotionText.setPosition(1110, windowSize.y - hudHeight - 85);

  tutorialText.setPosition(windowSize.x - backgroundRightWidth - 330, 0);

  // Set the size and position of the backgroundRight rectangle
  backgroundRight.setSize(sf::Vector2f(
      250, windowSize.y - hudHeight - 200));  // Full height minus the HUD
  backgroundRight.setPosition(windowSize.x - backgroundRightWidth - 350,
                              0);  // Position it at the right of the window
}

// Update HUD elements based on player status
void HUD::update(float deltaTime) {
  // Update health and ammo texts
  healthText.setString("Health: " + std::to_string((int)(player.getHealth())));
  ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
  scoreText.setString("Score: " + std::to_string(player.getScore()));
  Weapon* currentWeapon = player.getCurrentWeapon();  // Get the current weapon
  if (currentWeapon) {
    weaponText.setString("Weapon: " +
                         currentWeapon->getName());  // Set weapon name
  } else {
    weaponText.setString("Weapon: None");  // No weapon equipped
  }
  healthPotionText.setString("Health potions: " +
                             std::to_string(player.getHealthPotionCount()));
  tutorialText.setString(
      " Controls\n\n Movement: WASD\n Shoot: Space\n Pickup: E\n Use Heals: "
      "R\n\n Survive and\n defeat as many\n enemies as you\n can!");

  // Update the message timer
  elapsedTime += deltaTime;

  // Check if it's time to show a new message
  if (elapsedTime >= messageInterval) {
    // Select a random message
    messageIndex = rand() % messages.size();
    showMessage = true;
    elapsedTime = 0;  // Reset timer
  }

  // Manage message visibility duration
  if (showMessage) {
    if (elapsedTime >= messageDuration) {
      showMessage = false;  // Hide the message after duration
    }
  }
}

// Draw HUD on the screen
void HUD::draw(sf::RenderWindow& window) {
  window.draw(background);  // Draw the background rectangle first
  window.draw(backgroundRight);
  window.draw(healthText);
  window.draw(ammoText);
  window.draw(scoreText);
  window.draw(weaponText);
  window.draw(healthPotionText);
  window.draw(tutorialText);

  if (showMessage) {
    sf::Text messageText;
    messageText.setFont(font);
    messageText.setCharacterSize(30);
    messageText.setFillColor(sf::Color::White);
    messageText.setString(messages[messageIndex]);
    messageText.setPosition(backgroundRight.getPosition().x + 20,
                            500);  // Adjust position as needed
    window.draw(messageText);
  }
}

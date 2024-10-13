// HUD class contains the hud for the game. There are two main parts:  the text
// displayed and the boxes to indicate the text

#include "HUD.h"

// constructor
HUD::HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player)
    : player(player),
      font(font),
      showMessage(false),
      messageDuration(3),
      messageInterval(5),
      elapsedTime(0),
      messageIndex(0) {
  // initialise HUD background
  background.setFillColor(sf::Color::Black);       // background color is black
  background.setOutlineThickness(5);               //  outline thickness
  background.setOutlineColor(sf::Color::Magenta);  //  outline color to magenta

  backgroundRight.setFillColor(sf::Color::Black);  // background color is black
  backgroundRight.setOutlineThickness(5);          //  outline thickness
  backgroundRight.setOutlineColor(
      sf::Color::Magenta);  //  outline color to magenta

  // health
  healthText.setFont(font);
  healthText.setCharacterSize(40);
  healthText.setFillColor(sf::Color::Green);

  // ammo
  ammoText.setFont(font);
  ammoText.setCharacterSize(40);
  ammoText.setFillColor(sf::Color::Cyan);

  // score
  scoreText.setFont(font);
  scoreText.setCharacterSize(40);
  scoreText.setFillColor(sf::Color::Yellow);

  // weapon
  weaponText.setFont(font);
  weaponText.setCharacterSize(40);
  weaponText.setFillColor(sf::Color::White);

  // health potion
  healthPotionText.setFont(font);
  healthPotionText.setCharacterSize(40);
  healthPotionText.setFillColor(sf::Color::Red);

  // tutorial text
  tutorialText.setFont(font);
  tutorialText.setCharacterSize(30);
  tutorialText.setFillColor(sf::Color::White);

  updatePosition(windowSize);
}

// position of first HUD is to be at the bottom of the screen and second is to
// the right
void HUD::updatePosition(const sf::Vector2f& windowSize) {
  float hudHeight = 100;
  float backgroundRightWidth = 100;

  background.setSize(sf::Vector2f(
      windowSize.x - 500,
      hudHeight));  // full width of the game adjusted using trial and error
  background.setPosition(
      0,
      windowSize.y - hudHeight -
          110);  // positioned below the game adjusted with trial and error

  //
  backgroundRight.setSize(sf::Vector2f(
      250, windowSize.y - hudHeight - 200));  // height adjusted with trial and error
  backgroundRight.setPosition(windowSize.x - backgroundRightWidth - 350,
                              0);  // position it at the right of the window

  // the positions of the texts are properly adjusted
  // this section of text is at the bottom HUD
  healthText.setPosition(10, windowSize.y - hudHeight - 85);
  ammoText.setPosition(230, windowSize.y - hudHeight - 85);
  scoreText.setPosition(430, windowSize.y - hudHeight - 85);
  weaponText.setPosition(710, windowSize.y - hudHeight - 85);
  healthPotionText.setPosition(1110, windowSize.y - hudHeight - 85);

  // this section of text is at the right HUD
  tutorialText.setPosition(windowSize.x - backgroundRightWidth - 330, 0);
}

// function to update HUD elements based on player status
void HUD::update() {
  // update the health, ammo, score, weapon and tutorial texts
  healthText.setString("Health: " + std::to_string((int)(player.getHealth())));
  ammoText.setString("Ammo: " + std::to_string(player.getAmmo()));
  scoreText.setString("Score: " + std::to_string(player.getScore()));
  Weapon* currentWeapon = player.getCurrentWeapon();
  if (currentWeapon) {
    weaponText.setString("Weapon: " +
                         currentWeapon->getName());  // weapon name
  } else {
    weaponText.setString("Weapon: None");  // if no weapon equipped
  }
  healthPotionText.setString("Health potions: " +
                             std::to_string(player.getHealthPotionCount()));
  tutorialText.setString(
      " Controls\n\n Movement: WASD\n Shoot: Space\n Pickup: E\n Use Heals: "
      "R\n\n Survive and\n defeat as many\n enemies as you\n can!\n\n Pickup "
      "different\n weapons as you \nshoot enemies \n\n The maximum\n number of "
      "heals\n held at once\n is 5");
}

// draw the HUD on the screen
void HUD::draw(sf::RenderWindow& window) {
  window.draw(background); 
  window.draw(backgroundRight);
  window.draw(healthText);
  window.draw(ammoText);
  window.draw(scoreText);
  window.draw(weaponText);
  window.draw(healthPotionText);
  window.draw(tutorialText);
}

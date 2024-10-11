#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cstdlib> // For rand()
#include <ctime>   // For time()

class HUD {
public:
    HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player);
    void updatePosition(const sf::Vector2f& windowSize);
    void update();
    void draw(sf::RenderWindow& window);

private:
    Player& player;
    sf::Font& font;
    sf::RectangleShape background; // Background for bottom HUD
    sf::RectangleShape backgroundRight; //background for right HUD
    sf::Text healthText; // Health text
    sf::Text ammoText; // Ammo text
    sf::Text scoreText; // Score text
    sf::Text weaponText; //weapon text
    sf::Text healthPotionText; //health potion text
    sf::Text tutorialText; //tutorial text
    std::vector<std::string> messages;
    bool showMessage;
    float messageDuration; // Time for which the message will be displayed
    float messageInterval; // Time interval for showing new messages
    float elapsedTime;     // Timer for tracking elapsed time
    size_t messageIndex;   // Index of the currently displayed message
  
};

#endif // HUD_H

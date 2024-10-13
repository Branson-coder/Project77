//header file for the hud class
#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <cstdlib> 
#include <ctime>

class HUD {
public:
    HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player); //constructor
    void updatePosition(const sf::Vector2f& windowSize);
    void update();
    void draw(sf::RenderWindow& window);

private:
    Player& player;
    sf::Font& font;
    sf::RectangleShape background; 
    sf::RectangleShape backgroundRight;
    sf::Text healthText;
    sf::Text ammoText; 
    sf::Text scoreText; 
    sf::Text weaponText; 
    sf::Text healthPotionText; 
    sf::Text tutorialText;
    std::vector<std::string> messages;
    bool showMessage;
    float messageDuration;
    float messageInterval; 
    float elapsedTime;    
    size_t messageIndex; 
  
};

#endif // HUD_H

#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class HUD {
public:
    HUD(sf::Font& font, const sf::Vector2f& windowSize, Player& player);
    void updatePosition(const sf::Vector2f& windowSize);
    void update();
    void draw(sf::RenderWindow& window);

private:
    Player& player;
    sf::RectangleShape background; // Background for HUD
    sf::Text healthText; // Health text
    sf::Text ammoText; // Ammo text
    sf::Text scoreText; // Score text
    sf::Text weaponText; //weapon text
    sf::Text healthPotionText; //health potion text
};

#endif // HUD_H

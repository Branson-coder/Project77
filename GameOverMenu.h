// header file for game over menu
#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include <SFML/Graphics.hpp>
#include <string>

class GameOverMenu {
public:
    GameOverMenu(const sf::Font& font, const std::string& score); //constructor
    void draw(sf::RenderWindow& window); //function to draw text in window


private:
    sf::Text gameOverText;
    sf::Text scoreText;
    sf::Text instructionText;
};

#endif

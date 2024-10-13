#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(float width, float height); //constructor
    void draw(sf::RenderWindow &window); //draw the text in window
    void moveUp(); //move selection up
    void moveDown(); //down
    int getSelectedItemIndex() const;

private:
    sf::Font font;
    sf::Text title;
    sf::Text startText;
    sf::Text exitText;
    int selectedItemIndex;
    void updateSelection();
};

#endif // MENU_H

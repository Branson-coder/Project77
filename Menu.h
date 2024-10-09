#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu(float width, float height);
    void draw(sf::RenderWindow &window);
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    sf::Font font;
    sf::Text title;
    sf::Text startText;
    sf::Text tutorialText;
    sf::Text exitText;
    int selectedItemIndex;
    void updateSelection();
};

#endif // MENU_H

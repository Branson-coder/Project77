#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class Item {
private:
    sf::Vector2f itemPosition; 
    std::string itemType;      
    bool isPickedUp;           
    sf::RectangleShape shape;  

public:
    Item(sf::Vector2f position, std::string& type);
   
    ~Item();

    void collect();

    sf::Vector2f getPosition();

    bool getIsPickedUp();

    virtual void Draw(sf::RenderWindow& window);

    virtual void effect() = 0;
};

#endif
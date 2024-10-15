#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Collider.h"

class Item {
protected:
    sf::Vector2f itemPosition; // Position of the item in the game world
    std::string itemType;      // Type of the item (e.g., "ammo", "healing")
    bool isPickedUp;           // Indicates if the item has been picked up
    sf::RectangleShape shape;  // The graphical representation of the item
    Collider collider;

public:
    // Constructor should take the type as a const reference
    Item(sf::Vector2f position, const std::string& type); // Use const reference for string

    virtual ~Item(); // Destructor

    void collect(); // Marks the item as collected

    void setPosition(sf::Vector2f position);

    sf::Vector2f getPosition() const; // Get the item position (added const)

    bool getIsPickedUp() const; // Check if the item is picked up (added const)

    virtual void Draw(sf::RenderWindow& window); // Draw the item in the window

    virtual void effect() = 0; // Pure virtual function for effects of items

    Collider& GetCollider(){
        return collider;
    }
};

#endif
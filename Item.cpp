#include "Item.h"

// Constructor
Item::Item(sf::Vector2f position, const std::string& type) 
    : itemPosition(position), itemType(type), isPickedUp(false), collider(shape) 
{
    shape.setSize(sf::Vector2f(30.0f, 30.0f)); // Set a default size for the item
    shape.setPosition(itemPosition); // Set the position of the shape
}

// Destructor
Item::~Item() 
{
    // No dynamically allocated memory to clean up in this class
}

// Marks the item as collected
void Item::collect() 
{
    isPickedUp = true; // Set isPickedUp to true
}

void Item::setPosition(sf::Vector2f position) {
    itemPosition = position;
    shape.setPosition(itemPosition); // Update the shape's position as well
}

// Get the position of the item
sf::Vector2f Item::getPosition() const 
{
    return itemPosition; // Return the position
}

// Check if the item is picked up
bool Item::getIsPickedUp() const 
{
    return isPickedUp; // Return the pickup status
}

// Draw the item on the window
void Item::Draw(sf::RenderWindow& window) 
{
    if (!isPickedUp) // Only draw if the item has not been picked up
    {
        window.draw(shape); // Draw the item's shape
    }
}

// Effect is pure virtual; derived classes will implement this
void Item::effect() 
{
    // This function will be overridden in derived classes
}
#include "Item.h"

// Constructor
Item::Item(sf::Vector2f position, const std::string& type)
    : itemPosition(position), itemType(type) {
  shape.setSize(
      sf::Vector2f(30.0f, 30.0f));  // Set a default size for the items
  shape.setPosition(itemPosition);  // Set the position of the shape
}

// Destructor
Item::~Item() {}

// Set position of the item
void Item::setPosition(sf::Vector2f position) {
  itemPosition = position;
  shape.setPosition(itemPosition);
}

// Get the position of the item
sf::Vector2f Item::getPosition() const { return itemPosition; }

void Item::Draw(sf::RenderWindow& window) {
  window.draw(shape);  // Draw the item shape
}

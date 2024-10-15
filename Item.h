#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>

class Item {
 protected:
  sf::Vector2f itemPosition;  // Position of the item
  std::string itemType;       // Type of item
  sf::RectangleShape shape;   // The graphical representation of the item

 public:
  Item(sf::Vector2f position, const std::string& type);  // Constructor for item

  virtual ~Item();  // Destructor

  void setPosition(sf::Vector2f position);  // Set the position

  sf::Vector2f getPosition() const;  // Get the item position

  virtual void Draw(sf::RenderWindow& window);  // Draw the item in the window
};

#endif
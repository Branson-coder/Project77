#include "Heals.h"

#include <iostream>

// constructor for heals class
Heals::Heals(sf::Vector2f position, sf::Texture* texture)
    : Item(position, "Healing Item")  // Base class constructor
{
  shape.setTexture(texture);                  // texture of heals
  shape.setSize(sf::Vector2f(50.0f, 50.0f));  // size of heals
  shape.setPosition(position);                // position of heals.
}

// Destructor
Heals::~Heals() {}

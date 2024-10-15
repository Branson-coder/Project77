#ifndef HEALS_H
#define HEALS_H

#include "Item.h"

class Heals : public Item {
 public:
  // constructor
  Heals(sf::Vector2f position, sf::Texture* texture);

  // Override destructor
  ~Heals() override;
};

#endif
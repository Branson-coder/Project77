#ifndef LASERGUN_H
#define LASERGUN_H

#include "AssaultRifle.h"

// Base class for the laser gun
class LaserGun : public AssaultRifle {
 public:
  // Constructor
  LaserGun(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex,
           const std::string& name);

  // Override the fire function
  void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
};

#endif
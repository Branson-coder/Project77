#ifndef ASSAULTRIFLE_H
#define ASSAULTRIFLE_H

#include "Weapon.h"

// Base clas of AssaultRifle weapons and inherits from Weapon class
class AssaultRifle : public Weapon {
public:

    // AssaultRifle constructor 
    AssaultRifle(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name);

    // Overrides the fire function from weapon class
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;

    // Overrides the getDamage function from weapon class
    float getDamage() const override;

protected:
    int burstFireRounds;  // For burst fire in AssaultRifle weapons
};

#endif

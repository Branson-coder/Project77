#ifndef AK47_H
#define AK47_H

#include "AssaultRifle.h"

// Base class definition for AK47 weapon and inherits from AssaultRifle
class AK47 : public AssaultRifle {
public:

    // Constructor
    AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex);

    //Overrides fire function
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    
};

#endif



#ifndef M16_H
#define M16_h

#include "AssaultRifle.h"

// Base class for M16
class M16 : public AssaultRifle {
public:

    // Constructor 
    M16(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex);

    // Overrides the fire function
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    
};

#endif

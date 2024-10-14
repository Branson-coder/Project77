#ifndef AK47_H
#define AK47_H

#include "AssaultRifle.h"

// Base class for AK47 weapon and inherits from AssaultRifle
class AK47 : public AssaultRifle {
public:
    AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name);

    //Overrides fire function
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    
};

#endif



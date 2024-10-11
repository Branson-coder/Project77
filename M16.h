#ifndef M16_H
#define M16_h

#include "AssaultRifle.h"

class M16 : public AssaultRifle {
public:
    M16(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex);

    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    
};

#endif

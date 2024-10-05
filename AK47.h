#ifndef AK47_H
#define AK47_H

#include "AssaultRifle.h"

class AK47 : public AssaultRifle {
public:
    AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex);

    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
};

#endif



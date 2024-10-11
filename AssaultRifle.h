#ifndef ASSAULTRIFLE_H
#define ASSAULTRIFLE_H

#include "Weapon.h"

class AssaultRifle : public Weapon {
public:
    AssaultRifle(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name);

    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    float getDamage() const override;

protected:
    int burstFireRounds;  
};

#endif

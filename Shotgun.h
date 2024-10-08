#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

class Shotgun : public Weapon{
    public:
    Shotgun(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTexture);
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
    float getDamage() const override;

    protected:
    int spread;
};

#endif
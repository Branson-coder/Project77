#ifndef SHOTGUN_H
#define SHOTGUN_H
#include "Weapon.h"

// Base class for shotgun weapons
class Shotgun : public Weapon{
    public:
    // Shotgun contrcutor for shotgun weapons
    Shotgun(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTexture, const std::string& name);

    // Overridden fire function from Weapon
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;

    // Overridden getDamage function from Weapon
    float getDamage() const override;

    protected:

    // For knockback against enemies
    int knockback; 
};

#endif
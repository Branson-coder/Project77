#ifndef WEAPON_H
#define WEAPON_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
class Weapon{
Weapon(sf::Texture *texture, sf::Vector2f size, float fireRate, float damage);

virtual void fire() = 0;
virtual float getDamage() = 0;

sf::RectangleShape getBody() const;
void setPosition(sf::Vector2f position);

protected:
    float damage;
    float fireRate;
    int maxAmmo;    
    sf::RectangleShape body;
};

#endif
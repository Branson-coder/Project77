#include "Weapon.h"

Weapon::Weapon(sf::Texture *texture, sf::Vector2f size, float fireRate, float damage):
damage(damage), fireRate(fireRate), maxAmmo(20){
    body.setSize(size);
    body.setTexture(texture);
}

sf::RectangleShape Weapon::getBody() const {
    return body;
}

void Weapon::setPosition(sf::Vector2f position) {
    body.setPosition(position);
}
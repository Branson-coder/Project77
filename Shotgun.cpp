#include "Shotgun.h"
#include <cmath>

// Constructor
Shotgun::Shotgun(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex)
    : Weapon(texture, size, 0.1f, 20.0f), spread(3), takeOff(10)
{
    projectileTexture = *projectileTex;  
    maxAmmo = 90;  
    currentAmmo = maxAmmo;
}

// Fire method implementation
void Shotgun::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= spread) {
        for (int i = 0; i < spread; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 700.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
        }
        currentAmmo -= takeOff;
        std::cout << " Shotgun fired " << spread << " rounds. Ammo left: " << currentAmmo << std::endl;
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl; // might get rid of the burst 
    }
}

// Get damage implementation
float Shotgun::getDamage() const {
    return damage;
}

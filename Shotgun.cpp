#include "Shotgun.h"
#include <cmath>

// Constructor for base Shotgun class
Shotgun::Shotgun(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex, const std::string& name)
    : Weapon(texture, size, 0.1f, 20.0f, name), 
    knockback(3)
{
    projectileTexture = *projectileTex;  
    maxAmmo = 90;  
    currentAmmo = maxAmmo;
}

// Basic fire implementation for a Shotgun
void Shotgun::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);

    // Iterates over knockback value to simulate a knockback effect
    if (currentAmmo >= knockback) {
        for (int i = 0; i < knockback; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 700.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);

            // Will create no more than three projectiles here 
        }
        currentAmmo -= 10; // arbitrary value
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl; // might get rid of the burst 
    }
}

// Overrides and gets damage implementation for shotgun weapons
float Shotgun::getDamage() const {
    return damage;
}

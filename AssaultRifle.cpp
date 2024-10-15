// This is the base class for the Assaultrifle weapons and contains methods such as
// fire implementation specific to the gun 

#include "AssaultRifle.h"
#include <cmath>

// Constructor for AssaultRifle
AssaultRifle::AssaultRifle(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name)
    : Weapon(texture, size, 0.1f, 20.0f, name), burstFireRounds(3)  
{
    projectileTexture = projectileTex;  
    maxAmmo = 120;  
    currentAmmo = maxAmmo;
}

// Basic fire implementation framework and will change for derived weapons
void AssaultRifle::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= burstFireRounds) {
        
        // Shoots a burst of projectiles with specific values for each weapon
        for (int i = 0; i < burstFireRounds; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 700.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
            startPosition += direction * 50.0f;
        }

        currentAmmo -= 4; // Changeable number for different AssaultRifle guns
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl; 
    }
}

// Get damage implementation from derived guns
float AssaultRifle::getDamage() const {
    return damage;
}

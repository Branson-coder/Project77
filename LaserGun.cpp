#include "LaserGun.h"
#include <cmath>

// Constructor
LaserGun::LaserGun(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name)
    : AssaultRifle(texture, size, projectileTex, name) 
{
    burstFireRounds = 40;  
    damage = 5.0f;        
    fireRate = 0.08f;      
    maxAmmo = 1000;         
    currentAmmo = maxAmmo;
}

void LaserGun::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(40.0f, 40.0f);

    // Check if there's enough ammo to fire all projectiles
    if (currentAmmo >= burstFireRounds) {
        for (int i = 0; i < 40; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 800.0f);
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);
            projectiles.push_back(newProjectile);

            startPosition += direction * 5.0f;  // Adjust spacing between projectiles as needed
        }

        // Decrease ammo based on the number of projectiles fired
        currentAmmo -= 100; // Adjust based on how many projectiles are fired
    } else {
        std::cout << "Not enough ammo to fire." << std::endl;
    }
}
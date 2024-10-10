#include "SawedOff.h"
#include <cmath>

// Constructor
SawedOff::SawedOff(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex)
    : Shotgun(texture, size, projectileTex)
{
    spread = 5;  // AK-47 fires 5 rounds per burst somehow visually
    damage = 25.0f;        
    fireRate = 0.08f;      
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

void SawedOff::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= spread) {
        for (int i = 0; i < spread; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
        }
        currentAmmo -= spread;
        std::cout << "SawedOff fired " << spread << " rounds. Ammo left: " << currentAmmo << std::endl;
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

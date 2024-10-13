#include "M16.h"
#include <cmath>

// Constructor
M16::M16(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name)
    : AssaultRifle(texture, size, projectileTex, "M16")
{
    burstFireRounds = 4;  
    damage = 16.0f;            
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

void M16::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(70.0f, 70.0f);
    if (currentAmmo > burstFireRounds) {
        for (int i = 0; i < burstFireRounds; i++) {
        
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction,  800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
            startPosition += direction * 50.0f;

        }
        currentAmmo -= 6;
        
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

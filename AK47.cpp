#include "AK47.h"
#include <cmath>

// Constructor
AK47::AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name)
    : AssaultRifle(texture, size, projectileTex, "AK47")
{
    burstFireRounds = 1; 
    damage = 25.0f;              
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

void AK47::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(70.0f, 70.0f);
    if (currentAmmo > 0) {
        
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction,  800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
            
        currentAmmo -= 4;
        
        std::cout << "AK-47 fired " << burstFireRounds << " rounds. Number of projectiles now: " << projectiles.size() << std::endl;
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

#include "AK47.h"
#include <cmath>

// Constructor for the AK47 
AK47::AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex)
    : AssaultRifle(texture, size, projectileTex, "AK47")
{
    burstFireRounds = 2;    // Changed the value to shoot out 2 projectiles per shot
    damage = 25.0f;         // Accesses damage variable       
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

// Fire logic with the burstFireRounds of AK47
void AK47::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(70.0f, 70.0f);
    if (currentAmmo > 0) {

        //Will 
        for (int i = 0; i < burstFireRounds; i++) {
        
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction,  800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
            startPosition += direction * 50.0f;

        }
        currentAmmo -= 4;
        
    
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

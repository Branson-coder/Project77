#include "M16.h"
#include <cmath>

// Constructor
M16::M16(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex, const std::string& name)
    : AssaultRifle(texture, size, projectileTex, "M16")
{
    burstFireRounds = 2;  
    damage = 16.0f;        
    fireRate = 0.08f;      
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

void M16::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(70.0f, 70.0f);
    if (currentAmmo > burstFireRounds) {
        
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction,  800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);

            sf::Vector2f offsetPosition = startPosition + direction * 100.0f; 
            Projectile newProjectile1(&projectileTexture, offsetPosition, projectileSize, direction,  800.0f);  
            newProjectile1.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile1);


            
        currentAmmo -= 6;
        
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

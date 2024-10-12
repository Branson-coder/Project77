#include "Pump.h"
#include <cmath>

// Constructor
Pump::Pump(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex, const std::string& name)
    : Shotgun(texture, size, projectileTex, "Pump")
{
    push = 7;  
    damage = 4.0f;          
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
    takeOff = 20;
}

void Pump::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= 10) {
        for (int i = 0; i < push; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 800.0f);  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);

        sf::Vector2f slightlyOffsetDirection = direction + sf::Vector2f(0.1f, 0.1f); 
        float magnitude = sqrt(slightlyOffsetDirection.x * slightlyOffsetDirection.x + slightlyOffsetDirection.y * slightlyOffsetDirection.y);
        if (magnitude != 0) {
            slightlyOffsetDirection /= magnitude;  
        }

        Projectile projectile2(&projectileTexture, startPosition, projectileSize, slightlyOffsetDirection, 800.0f);  
        projectile2.setRotation(atan2(slightlyOffsetDirection.y, slightlyOffsetDirection.x) * 180 / 3.14159265);  
        projectiles.push_back(projectile2);

        sf::Vector2f OffsetDirection = direction + sf::Vector2f(-0.1f, -0.1f); 
        float magnitude1 = sqrt(slightlyOffsetDirection.x * OffsetDirection.x + OffsetDirection.y * slightlyOffsetDirection.y);
        if (magnitude1 != 0) {
            OffsetDirection /= magnitude1;  
        }

        Projectile projectile3(&projectileTexture, startPosition, projectileSize, OffsetDirection, 800.0f);  
        projectile3.setRotation(atan2(OffsetDirection.y, OffsetDirection.x) * 180 / 3.14159265);  
        projectiles.push_back(projectile3);
        
        }

        

        
        
        currentAmmo -= takeOff;
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

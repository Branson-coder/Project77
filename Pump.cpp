#include "Pump.h"
#include <cmath>

// Constructor for the Pump shotgun
Pump::Pump(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex)
    : Shotgun(texture, size, projectileTex, "Pump") // initialises gun texture, projectile texture, 
                                                    // size and name using Shotgun Constructor
{
    knockback = 7; // Knockback power equates to 7 bullets  
    damage = 4.0f; // Accesses damage variable  
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

// Fire implementation for the Pump
void Pump::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= 10) {

        //Iterates over knockback value to increase enemy knockback but with only three visual projectiles
        for (int i = 0; i < knockback; ++i) {

        Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 800.0f);  
        newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
        projectiles.push_back(newProjectile);

        // Creates another projectile which is slightly offset to simulate shotgun spread
        sf::Vector2f slightlyOffsetDirection = direction + sf::Vector2f(0.1f, 0.1f); 


        float magnitude = sqrt(slightlyOffsetDirection.x * slightlyOffsetDirection.x + slightlyOffsetDirection.y * slightlyOffsetDirection.y);
        if (magnitude != 0) {
            slightlyOffsetDirection /= magnitude;  
        }

        Projectile projectile2(&projectileTexture, startPosition, projectileSize, slightlyOffsetDirection, 800.0f);  
        projectile2.setRotation(atan2(slightlyOffsetDirection.y, slightlyOffsetDirection.x) * 180 / 3.14159265);  
        projectiles.push_back(projectile2);

        // Third projectile for shotgun spread
        sf::Vector2f OffsetDirection = direction + sf::Vector2f(-0.1f, -0.1f); 
        float magnitude1 = sqrt(slightlyOffsetDirection.x * OffsetDirection.x + OffsetDirection.y * slightlyOffsetDirection.y);
        if (magnitude1 != 0) {
            OffsetDirection /= magnitude1;  
        }

        Projectile projectile3(&projectileTexture, startPosition, projectileSize, OffsetDirection, 800.0f);  
        projectile3.setRotation(atan2(OffsetDirection.y, OffsetDirection.x) * 180 / 3.14159265);  
        projectiles.push_back(projectile3);
        
        }

        

        
        // Uses 10 ammo after every fire
        currentAmmo -= 10;
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

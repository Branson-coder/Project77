#include "SawedOff.h"
#include <cmath>

// Constructor for SawedOff gun
SawedOff::SawedOff(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex)
    : Shotgun(texture, size, projectileTex, "Sawed Off")
{
    knockback = 5;  // Knockback power equates to 5 bullets
    damage = 5.0f;  // Accesses damage variable 
    maxAmmo = 120;         
    currentAmmo = maxAmmo;
}

//Creates three projectiles with changeable knockback value 
void SawedOff::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(50.0f, 50.0f);
    if (currentAmmo >= 10) {

        // Iterates over each value to create knockback but visually only creates three projectiles 
        for (int i = 0; i < knockback; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction, 800.0f);

            // Sets the rotation of the projectile visual  
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile);
        
        // Creates another projectile which is slightly offset to simulate shotgun spread
        sf::Vector2f slightlyOffsetDirection = direction + sf::Vector2f(0.1f, 0.1f); 
        float magnitude = sqrt(slightlyOffsetDirection.x * slightlyOffsetDirection.x + slightlyOffsetDirection.y * slightlyOffsetDirection.y);
        if (magnitude != 0) {
            slightlyOffsetDirection /= magnitude;  
        }

        Projectile projectile2(&projectileTexture, startPosition, projectileSize, slightlyOffsetDirection, 800.0f);  

        // Sets the rotation of the projectile visual 
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

        
        
        currentAmmo -= 6;
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

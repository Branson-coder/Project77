#include "M16.h"
#include <cmath>

// Constructor for the M16 
M16::M16(sf::Texture* texture, sf::Vector2f size, sf::Texture projectileTex)
    : AssaultRifle(texture, size, projectileTex, "M16") 
{
    burstFireRounds = 4;  // Changed the value to shoot out 4 projectiles per shot
    damage = 16.0f;       // Accesses damage variable      
    maxAmmo = 120;        // The capacity of ammunition for the M16
    currentAmmo = maxAmmo; // Initialise the currentAmmo at the start to maxAmmo
}

// Fire implementation for the M16
void M16::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    sf::Vector2f projectileSize(70.0f, 70.0f);
    if (currentAmmo > burstFireRounds) { // Ensure that currentAmmo is enough for firing
        for (int i = 0; i < burstFireRounds; i++) { //Iterates over burstFireRounds to shoot a burst of projectile

            // Creates a new projectile object
            Projectile newProjectile(&projectileTexture, startPosition, projectileSize, direction,  800.0f); 
            
            // Calculates the angle based on projectile directions and set the visual rotation as such
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  
            projectiles.push_back(newProjectile); // Pushes the newly created projectile into the vector
            startPosition += direction * 50.0f;   // sets each bust projectile slightly apart

        }
        currentAmmo -= 6; // Take away 6 from the ammo
        
        
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

#include "AK47.h"
#include <cmath>

// Constructor
AK47::AK47(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex)
    : AssaultRifle(texture, size, projectileTex)
{
    burstFireRounds = 5;  // AK-47 fires 5 rounds per burst
    damage = 25.0f;        // Increased damage
    fireRate = 0.08f;      // Faster fire rate
    maxAmmo = 120;         // Increased max ammo
    currentAmmo = maxAmmo;
}

// Fire method implementation
void AK47::fire(sf::Vector2f direction, sf::Vector2f startPosition) {
    if (currentAmmo >= burstFireRounds) {
        for (int i = 0; i < burstFireRounds; ++i) {
            Projectile newProjectile(&projectileTexture, startPosition, direction, 800.0f);  // Example speed
            newProjectile.setRotation(atan2(direction.y, direction.x) * 180 / 3.14159265);  // Set rotation based on direction
            projectiles.push_back(newProjectile);
        }
        currentAmmo -= burstFireRounds;
        std::cout << "AK-47 fired " << burstFireRounds << " rounds. Ammo left: " << currentAmmo << std::endl;
    } else {
        std::cout << "Not enough ammo to fire burst." << std::endl;
    }
}

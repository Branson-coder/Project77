#include <cassert>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "AK47.h"
#include "M16.h"
#include "LaserGun.h"
#include "SawedOff.h"
#include "Pump.h"

// g++ -o FireTest WeaponFireTest.cpp Weapon.cpp AssaultRifle.cpp AK47.cpp Projectile.cpp -lsfml-graphics -lsfml-window -lsfml-system

void testAK47Fire() {
    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("Projectile.png");

    sf::Texture akTexture;
    akTexture.loadFromFile("AK47.png");

    AK47 ak47(&akTexture, sf::Vector2f(50.0f, 50.0f), projectileTexture);

    // Initialise a  specific direction from a starting position
    sf::Vector2f direction(1.0f, 0.0f); 
    sf::Vector2f startPosition(100.0f, 100.0f); 

    // Fire the weapon
    ak47.fire(direction, startPosition);

    // Assert that the correct projectiles were created from the fire and pushed into the vector
    const std::vector<Projectile>& projectiles = ak47.getProjectiles();
    assert(projectiles.size() == 2);  

    // Check properties of each projectile
    for (int i = 0; i < 2; ++i) {
        Projectile proj = projectiles[i];
        assert(proj.getPosition().x == startPosition.x + (i * 50.0f));  
        assert(proj.getSize() == sf::Vector2f(70.0f, 70.0f));  
    }

    std::cout << "AK47 fire() test passed!" << std::endl;
}

void testM16Fire() {
    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("Projectile.png");

    sf::Texture M16Texture;
    M16Texture.loadFromFile("M16.png");

    M16 m16(&M16Texture, sf::Vector2f(50.0f, 50.0f), projectileTexture);

    // Fire in a specific direction from a starting position
    sf::Vector2f direction(1.0f, 0.0f);  
    sf::Vector2f startPosition(100.0f, 100.0f);  

    // Fire the weapon
    m16.fire(direction, startPosition);

    // Assert that projectile creation
    const std::vector<Projectile>& projectiles = m16.getProjectiles();
    assert(projectiles.size() == 4);  

    // Assert properties of each projectile
    for (int i = 0; i < 4; ++i) {
        Projectile proj = projectiles[i];
        assert(proj.getPosition().x == startPosition.x + (i * 50.0f));  // Check position offset by direction
        assert(proj.getSize() == sf::Vector2f(70.0f, 70.0f));  
    }

    std::cout << "M16 fire() test passed!" << std::endl;
}

void testLaserGunFire() {
    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("Projectile.png");

    sf::Texture LasergunTexture;
    LasergunTexture.loadFromFile("LaserGun.png");

    LaserGun lasergun(&LasergunTexture, sf::Vector2f(50.0f, 50.0f), projectileTexture, "Lasergun");

    // Fire in a specific direction from a starting position
    sf::Vector2f direction(1.0f, 0.0f);  // Fire to the right
    sf::Vector2f startPosition(100.0f, 100.0f);  // Start position for the first shot

    // Fire the weapon
    lasergun.fire(direction, startPosition);

    // Assert that projectile creation
    const std::vector<Projectile>& projectiles = lasergun.getProjectiles();
    assert(projectiles.size() == 40);  

    // Assert properties of each projectile
    for (int i = 0; i < 40; ++i) {
        Projectile proj = projectiles[i];
        assert(proj.getPosition().x == startPosition.x + (i * 5.0f));  // Check position offset by direction
        assert(proj.getSize() == sf::Vector2f(40.0f, 40.0f));  
    }

    std::cout << "LaserGun fire() test passed!" << std::endl;
}
float normalizeAngle(float angle) {
    while (angle < 0) {
        angle += 360.0f;
    }
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }
    return angle;
}

void testPumpFire() {
    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("Projectile.png"); 

    sf::Texture pumpTexture;
    pumpTexture.loadFromFile("Pump.png");

    Pump pump(&pumpTexture, sf::Vector2f(50.0f, 50.0f), &projectileTexture);


    // Initialise a specific direction from a starting position
    sf::Vector2f direction(1.0f, 0.0f); // Direction for the projectile
    sf::Vector2f startPosition(100.0f, 100.0f); // Starting position

    // Fire the weapon
    pump.fire(direction, startPosition);

    // Assert that the correct projectiles were created and pushed into the vector
    const std::vector<Projectile>& projectiles = pump.getProjectiles();
    assert(projectiles.size() == 21);  // Should create 3 projectiles
    
    const float tolerance = 0.01f;

   for (int i = 0; i < 21; ++i) {
        Projectile proj = projectiles[i];
        
        // Check if the projectile is initialized with the correct size
        assert(proj.getSize() == sf::Vector2f(50.0f, 50.0f));
        
        // Calculate the expected rotation based on the index of the projectile
        float expectedRotation;
        if (i % 3 == 0) { // Main projectile
            expectedRotation = atan2(direction.y, direction.x) * 180 / 3.14159265;
        } else if (i % 3 == 1) { // First offset projectile
            sf::Vector2f offsetDirection = direction + sf::Vector2f(0.1f, 0.1f);
            float magnitude = sqrt(offsetDirection.x * offsetDirection.x + offsetDirection.y * offsetDirection.y);
            if (magnitude != 0) {
            offsetDirection /= magnitude;  
        }
            expectedRotation = atan2(offsetDirection.y, offsetDirection.x) * 180 / 3.14159265;
        } else { 
            sf::Vector2f OffsetDirection = direction + sf::Vector2f(-0.1f, -0.1f);
            float magnitude1 = sqrt(OffsetDirection.x * OffsetDirection.x + OffsetDirection.y * OffsetDirection.y);
            if (magnitude1 != 0) {
            OffsetDirection /= magnitude1; 
           
            expectedRotation = atan2(OffsetDirection.y, OffsetDirection.x) * 180 / 3.14159265;
        }

        
    }
         expectedRotation = normalizeAngle(expectedRotation);
        float actualRotation = normalizeAngle(proj.getRotation());
        std::cout << "Projectile " << i << ": Actual Rotation = " << proj.getRotation()
                  << ", Expected Rotation = " << expectedRotation << std::endl;
     
        assert(fabs(proj.getRotation() - expectedRotation) < tolerance);  // Use a tolerance to compare rotations
}
std::cout << "Pump fire() test passed!" << std::endl;

}



int main() {
    testAK47Fire();
    testM16Fire();
    testLaserGunFire();
    testPumpFire();
    std::cout<< "All tests passed"<<std::endl;

    return 0;
}

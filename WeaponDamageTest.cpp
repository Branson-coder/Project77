#include <iostream>
#include <SFML/Graphics.hpp>
#include <cassert>

#include "Weapon.h"
#include "AssaultRifle.h"
#include "Shotgun.h"
#include "AK47.h"
#include "M16.h"
#include "LaserGun.h"
#include "SawedOff.h"
#include "Pump.h"

 //g++ -o WeaponTest WeaponDamageTest.cpp Weapon.cpp AssaultRifle.cpp AK47.cpp Projectile.cpp M16.cpp LaserGun.cpp Pump.cpp SawedOff.cpp Shotgun.cpp -lsfml-graphics -lsfml-window -lsfml-system

void testM16Damage() {
    static sf::Texture akTexture;
    static bool akTextureLoaded = false;
  if (!akTextureLoaded) {
    if (!akTexture.loadFromFile("M16.png")) {
      std::cerr << "Error loading AK47 texture!"
                << std::endl;  
      return;
    }
    akTextureLoaded = true;
  }
  static sf::Texture projectileTexture;
  static bool projectileTexLoaded = false;
  if (!projectileTexLoaded) {
    if (!projectileTexture.loadFromFile("Projectile.png")) {
      std::cerr << "Error loading projectile texture!" << std::endl;
      return;
    }
    projectileTexLoaded = true;
  }
    M16 M16(&akTexture, sf::Vector2f(70.0f, 70.0f), projectileTexture);

    assert(M16.getDamage() == 16.0f); // Check damage value
    std::cout << "M16 damage test passed!" << std::endl;
}

void testAK47Damage() {
    static sf::Texture akTexture;
    static bool akTextureLoaded = false;
  if (!akTextureLoaded) {
    if (!akTexture.loadFromFile("AK47.png")) {
      std::cerr << "Error loading AK47 texture!"
                << std::endl;  
      return;
    }
    akTextureLoaded = true;
  }
  static sf::Texture projectileTexture;
  static bool projectileTexLoaded = false;
  if (!projectileTexLoaded) {
    if (!projectileTexture.loadFromFile("Projectile.png")) {
      std::cerr << "Error loading projectile texture!" << std::endl;
      return;
    }
    projectileTexLoaded = true;
  }
    AK47 ak47(&akTexture, sf::Vector2f(70.0f, 70.0f), projectileTexture);

    assert(ak47.getDamage() == 25.0f); // Check damage value
    std::cout << "AK47 damage test passed!" << std::endl;
}

void testLaserDamage() {
     static sf::Texture laserGunTexture;
  static bool laserTextureLoaded = false;
  if (!laserTextureLoaded) {
    if (!laserGunTexture.loadFromFile("LaserGun.png")) {
      std::cerr << "Error loading laser gun texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    laserTextureLoaded = true;
  }

  static sf::Texture projectileTexture;
  static bool projectileTexLoaded = false;
  if (!projectileTexLoaded) {
    if (!projectileTexture.loadFromFile("Projectile.png")) {
      std::cerr << "Error loading projectile texture!" << std::endl;
      return;
    }
    projectileTexLoaded = true;
  }
    LaserGun lasergun(&laserGunTexture, sf::Vector2f(70.0f, 70.0f), projectileTexture, "LaserGun");

    assert(lasergun.getDamage() == 5.0f); // Check damage value
    std::cout << "LaserGun damage test passed!" << std::endl;
}

void testSawedOffDamage(){
  static sf::Texture SawedOffTexture;
  static bool SawedOffTextureLoaded = false;
  if (!SawedOffTextureLoaded) {
    if (!SawedOffTexture.loadFromFile("SawedOff.png")) {
      std::cerr << "Error loading Sawed Off texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    SawedOffTextureLoaded = true;
  }
  static sf::Texture projectileTexture;
  projectileTexture.loadFromFile("Projectile.png");

 SawedOff sawedoff(&SawedOffTexture, sf::Vector2f(70.0f, 70.0f), &projectileTexture);

    assert(sawedoff.getDamage() == 5.0f); // Check damage value
    std::cout << "SawedOff damage test passed!" << std::endl;

}

void testPumpDamage(){
  static sf::Texture pumpTexture;
  static bool pumpTextureLoaded = false;
  if (!pumpTextureLoaded) {
    if (!pumpTexture.loadFromFile("Pump.png")) {
      std::cerr << "Error loading Pump texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    pumpTextureLoaded = true;
  }
  static sf::Texture projectileTexture;
  projectileTexture.loadFromFile("Projectile.png");

  Pump pump(&pumpTexture, sf::Vector2f(70.0f, 70.0f), &projectileTexture);

    assert(pump.getDamage() == 4.0f); // Check damage value
    std::cout << "Pump damage test passed!" << std::endl;


}



int main(){
     testAK47Damage();
     testM16Damage();
     testLaserDamage();
     testSawedOffDamage();
     testPumpDamage();
    std::cout << " All damage tests passed" << std::endl;
return 0;
}
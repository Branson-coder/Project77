#include <iostream>
#include <SFML/Graphics.hpp>
#include <cassert>
#include "Weapon.h"
#include "AssaultRifle.h"
#include "AK47.h"
#include "M16.h"
#include "SawedOff.h"
#include "Pump.h"



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
    M16 M16(&akTexture, sf::Vector2f(70.0f, 70.0f), projectileTexture, "AK47");

    assert(M16.getDamage() == 16.0f); // Check damage value
    std::cout << "AK47 damage test passed!" << std::endl;
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
    AK47 ak47(&akTexture, sf::Vector2f(70.0f, 70.0f), projectileTexture, "AK47");

    assert(ak47.getDamage() == 25.0f); // Check damage value
    std::cout << "M16 damage test passed!" << std::endl;
}






int main(){
     testAK47Damage();
     testM16Damage();
    std::cout << " All damage tests passed" << std::endl;
return 0;
}
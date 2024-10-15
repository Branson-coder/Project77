// This is the base class for all weapons inside the game and contains methods that will be
// inherited and altered specifically for corresponding types of weapons in derived classes
#include "Weapon.h"
#include "Projectile.h"

// Base weapon class constructor
Weapon::Weapon(sf::Texture* texture, sf::Vector2f size,
               float damage, const std::string& name)
    : damage(damage),
      maxAmmo(30), // arbitrary number
      currentAmmo(maxAmmo),
      weaponName(name) {
  body.setSize(size);
  body.setTexture(texture);
  body.setOrigin(size / 2.0f);
}

Weapon::~Weapon() {}

// Sets position of weapon when spawning
void Weapon::setPosition(sf::Vector2f position) { 
  body.setPosition(position); 
}

// Iterates over projectiles vector and updates their position with deltatime
void Weapon::updateProjectiles(float deltaTime, const sf::RenderWindow& window) {
  (void)window; 

  // Iterates over each projectile object and updates them according to deltaTime
  for (size_t i = 0; i < projectiles.size(); ++i) {
    projectiles[i].Update(deltaTime);
  }
}

// Iterates over projectiles vector and draws each projectile object
void Weapon::drawProjectiles(sf::RenderWindow& window) {

  // Iterates over the projectile objects and draws each 
  for (size_t i = 0; i < projectiles.size(); i++) {
    projectiles[i].Draw(window);
  }
}

// Draws the weapon body
void Weapon::Draw(sf::RenderWindow& window) { 
  window.draw(body);
}


// Return the current ammo count
int Weapon::getAmmo() {
  return currentAmmo;  
}

// Returns weapon position
sf::Vector2f Weapon::getPosition() const { 
  return body.getPosition(); 
  }


//  Returns weapon name
std::string Weapon::getName() const {
  return weaponName;  
}
#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Projectile.h"
#include "Collider.h"  
#include <string>

// Base class for all weapons in the game
class Weapon {
public:
    // Contstructor for a weapon object 
    Weapon(sf::Texture* texture, sf::Vector2f size, float fireRate, float damage, const std::string& name); 
    virtual ~Weapon();
    
    // Pure virtual function to fire projectile from a starting position at a certain direction
    virtual void fire(sf::Vector2f direction, sf::Vector2f startPosition) = 0;

    // Pure virtual function to return damage of the weapon
    virtual float getDamage() const = 0;

    

    // Function to draw the weapon
    void Draw(sf::RenderWindow& window);

    // Function to set the position of weapon when spawned
    void setPosition(sf::Vector2f position);

    // Updates the projectile state 
    void updateProjectiles(float deltaTime, const sf::RenderWindow& window);

    // Draws the projectile 
    void drawProjectiles(sf::RenderWindow& window);

    // Accesses the vector of projectiles and returns reference to the vector
    std::vector<Projectile>& getProjectiles()
	{
		return projectiles;
	}
    
    // Gets ammo of weapon
    int getAmmo();

    //Gets position
    sf::Vector2f getPosition() const; 

    // Gets name
    std::string getName() const;  

    // Initialises a vector of Projectile objects
    std::vector<Projectile> projectiles;

protected:
    float damage;
    float fireRate;
    int maxAmmo;
    int currentAmmo;
    sf::RectangleShape body;
    std::string weaponName;
    sf::Texture projectileTexture;        
};

#endif

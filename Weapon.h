#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Projectile.h"
#include "Collider.h"  

class Weapon {
public:
    Weapon(sf::Texture* texture, sf::Vector2f size, float fireRate, float damage);

    
    virtual void fire(sf::Vector2f direction, sf::Vector2f startPosition) = 0;
    virtual float getDamage() const = 0;

    
    sf::RectangleShape getBody() const;

    void Draw(sf::RenderWindow& window);
    void setPosition(sf::Vector2f position);

    
    void updateProjectiles(float deltaTime, const sf::RenderWindow& window);
    void drawProjectiles(sf::RenderWindow& window);

    
    Collider GetCollider(){
        return Collider(body);
    }

protected:
    float damage;
    float fireRate;
    int maxAmmo;
    int currentAmmo;
    sf::RectangleShape body;

    std::vector<Projectile> projectiles;  
    sf::Texture projectileTexture;        
};

#endif

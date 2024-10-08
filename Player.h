#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Collider.h"
#include "Weapon.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime,const sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() const { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }


    void takeDamage(float damage);  // New method to take damage
    bool isAlive() const { return health > 0; }  // Check if player is still alive

    void equipWeapon(Weapon* weapon);      
    void switchWeapon(int index);        
    void shoot(); 

    sf::Vector2f GetSize() const {
    return body.getSize();
    }
    
private:
    enum Direction { Up, Down, Left, Right };
    Direction facingDirection;

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool isMoving;
    float timeDelay;
    float health;  // Player health

    std::vector<Weapon*> inventory;  
    Weapon* currentWeapon; 
};

#endif

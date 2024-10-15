//header file for player class
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Collider.h"
#include "Weapon.h"
#include "Item.h"
#include "Heals.h"

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
    Weapon* getCurrentWeapon();

    void equipWeapon(Weapon* weapon);      
    void switchWeapon(int index);        
    void shoot(); 

    bool equipHeal(Heals* heal);        // Equip a healing item
    void useHeal();                     // Use healing item

    sf::Vector2f GetSize() const {
    return body.getSize();
    }

    void increaseScore(){score++;}
    
    int getAmmo();
    int getScore();
    std::string getWeapon();

    
    float getHealth() const;
    void setHealth(float health);
    int getHealthPotionCount();
    void gameOver();
    void setPosition(const sf::Vector2f& position) { body.setPosition(position);}
    
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
    int score;
    Weapon* currentWeapon; 
    Heals* healInventory[5];  // Array of healing items
    int healCount;  // Number of heals currently in inventory 
};

#endif

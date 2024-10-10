//header file for enemy class
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"


class Enemy {
protected:
    sf::RectangleShape body;
    Animation animation;
    std::vector<Projectile> projectiles;

    sf::Vector2f direction;
    sf::Vector2f movement;

    unsigned int row;
    float speed;
    float health;
    float damage;
    float currentSpeed;
    bool faceRight;
    bool active;

public:
    // constructor
    Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health, float speed);
    // destructor
    virtual ~Enemy();

    // Core Methods
    virtual void update(float deltaTime, const Player& player);
    virtual void draw(sf::RenderWindow& window);
    virtual void takeDamage(float damage);
    
    // getters
    sf::Vector2f getPosition() const { return body.getPosition(); }
    float getHealth() const { return health; }
    
    // For collision handling
     Collider GetCollider(){
        return Collider(body);
    }

    //controls whether enemy is alive or not
    bool isAlive() const { return health > 0; }

    //set position of the enemy with position
    void setPosition(sf::Vector2f position);
};

#endif // ENEMY_H

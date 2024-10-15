// this class is responsible for being the base class for the derived enemy
// classes. this introduces a base class that has core methods which will be
// adjusted in the derived classes

#include "Enemy.h"
#include <iostream>
//constructor for enemy class
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,
             float health, float speed)
    : animation(texture, imageCount, switchTime), speed(speed), health(health) {
        //set variables
  body.setOrigin(body.getSize() / 2.0f);
  body.setTexture(texture);
  faceRight = true;
  
}
//nothing in this update class as it will be modified in the derived classes
void Enemy::update(float deltaTime, const Player& player) {
  (void)deltaTime;
  (void)player;
}

//draws the enemy in the window
void Enemy::draw(sf::RenderWindow& window) { window.draw(body); }

//method for enemy to take damage
void Enemy::takeDamage(float damage) {
  health -= damage;
  if (health < 0) {
    health = 0;
  }
}

//set position of enemy
void Enemy::setPosition(sf::Vector2f position) {
    body.setPosition(position);
    
}

//destructor
Enemy::~Enemy() {}

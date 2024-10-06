#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health, float speed)
    : animation(texture, imageCount, switchTime), health(health), speed(speed)
{
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(texture);
    faceRight = true;
}

void Enemy::update(float deltaTime, const Player& player){}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Enemy::takeDamage(float damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
}

Enemy::~Enemy() {
}

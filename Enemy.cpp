#include "Enemy.h"
#include <iostream>

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float health, float speed)
    : animation(texture, imageCount, switchTime), health(health), speed(speed)
{
    body.setOrigin(body.getSize() / 2.0f);
    body.setTexture(texture);
    faceRight = true;
}

void Enemy::update(float deltaTime, const Player& player) {


    float xDif = player.GetPosition().x - body.getPosition().x;
    float yDif = player.GetPosition().y - body.getPosition().y;
	 row = 0; 

    movement = sf::Vector2f(0.0f, 0.0f);

    if (yDif < 0 && std::abs(yDif) > std::abs(xDif)) {
        direction = sf::Vector2f(0.0f, -1.0f);
        movement.y -= speed * deltaTime;
		row = 0;
		
    }
    else if (xDif > 0 && std::abs(xDif) > std::abs(yDif)) {
        direction = sf::Vector2f(1.0f, 0.0f);
        movement.x += speed * deltaTime;
		row = 2;
		
    }
    else if (xDif < 0 && std::abs(xDif) > std::abs(yDif)) {
        direction = sf::Vector2f(-1.0f, 0.0f);
        movement.x -= speed * deltaTime;
		row = 1;
		
    }
    else if (yDif > 0 && std::abs(yDif) > std::abs(xDif)) {
        direction = sf::Vector2f(0.0f, 1.0f);
        movement.y += speed * deltaTime;
		row = 3;
		
    }

        animation.Update(row, deltaTime);
        body.setTextureRect(animation.uvRect);
        body.move(movement);


}

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

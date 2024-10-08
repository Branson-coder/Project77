#include "TankyEnemy.h"
#include <cmath>

TankyEnemy::TankyEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : Enemy(texture, imageCount, 2.0f, 200.0f, 2.0f) {

    body.setSize(sf::Vector2f(100.0f, 100.0f)); // Set the size of the enemy
    body.setTexture(texture); // Set the texture
}

void TankyEnemy::update(float deltaTime, const Player& player)
{

  // set the enemy's origin to its center
  body.setOrigin(body.getSize() / 2.0f);  
    // Get the player and enemy's center positions
    sf::Vector2f playerCenter = player.GetPosition(); // get the player's center
    sf::Vector2f enemyCenter = body.getPosition();    // get the enemy's center

    // the direction vector between the enemy's center and the player's center
    sf::Vector2f directionToPlayer = playerCenter - enemyCenter;

    // method to normalise a direction vector for movement
    float length = std::sqrt(directionToPlayer.x * directionToPlayer.x + directionToPlayer.y * directionToPlayer.y);
    if (length != 0) {
        directionToPlayer /= length;
    }

    // movement is based on the normalized direction and speed
    movement = directionToPlayer * speed * deltaTime;

    // update the enemy's row (animation) based on the direction of movement
    if (directionToPlayer.y < 0 && std::abs(directionToPlayer.y) > std::abs(directionToPlayer.x)) {
        row = 3;  //  up
    }
    else if (directionToPlayer.x > 0 && std::abs(directionToPlayer.x) > std::abs(directionToPlayer.y)) {
        row = 2;  //  right
    }
    else if (directionToPlayer.x < 0 && std::abs(directionToPlayer.x) > std::abs(directionToPlayer.y)) {
        row = 1;  //  left
    }
    else if (directionToPlayer.y > 0 && std::abs(directionToPlayer.y) > std::abs(directionToPlayer.x)) {
        row = 0;  //  down
    }

    // animation update and move the enemy
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
}
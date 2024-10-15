// this normal enemy class is inherited from enemy, and is the most basic enemy
// with no outstanding abilities such as high health or fast speed
#include "NormalEnemy.h"
#include <cmath>

NormalEnemy::NormalEnemy(sf::Texture* texture, sf::Vector2u imageCount
                         )
    : Enemy(texture, imageCount, 2.0f, 150.0f, 2.0f) {
  body.setSize(sf::Vector2f(75.0f, 75.0f)); 
  body.setTexture(texture);                  
}
void NormalEnemy::update(float deltaTime, const Player& player) {
  // set the enemy's origin to its center
  body.setOrigin(body.getSize() / 2.0f);
  // the player and enemy's center positions
  sf::Vector2f playerCenter = player.GetPosition();  // get the player's center
  sf::Vector2f enemyCenter = body.getPosition();     // get the enemy's center

  // the direction vector between the enemy's center and the player's center
  sf::Vector2f directionToPlayer = playerCenter - enemyCenter;

  // method to normalise a direction vector for movement
  float length = std::sqrt(directionToPlayer.x * directionToPlayer.x +
                           directionToPlayer.y * directionToPlayer.y);
  if (length != 0) {
    directionToPlayer /= length;
  }

  // movement is based on the normalized direction and speed
  movement = directionToPlayer * speed * deltaTime;

  // update the enemy's row (animation) based on the direction of movement
  if (directionToPlayer.y < 0 &&
      std::abs(directionToPlayer.y) > std::abs(directionToPlayer.x)) {
    row = 1;  //  up
  } else if (directionToPlayer.x > 0 &&
             std::abs(directionToPlayer.x) > std::abs(directionToPlayer.y)) {
    row = 2;  //  right
  } else if (directionToPlayer.x < 0 &&
             std::abs(directionToPlayer.x) > std::abs(directionToPlayer.y)) {
    row = 3;  //  left
  } else if (directionToPlayer.y > 0 &&
             std::abs(directionToPlayer.y) > std::abs(directionToPlayer.x)) {
    row = 0;  //  down
  }

  // animation update and move the enemy
  animation.Update(row, deltaTime);
  body.setTextureRect(animation.uvRect);
  body.move(movement);
}

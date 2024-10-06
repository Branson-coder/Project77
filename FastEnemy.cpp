#include "FastEnemy.h"

FastEnemy::FastEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : Enemy(texture, imageCount, 2.0f, 100.0f, 5.0f) {

    body.setSize(sf::Vector2f(50.0f, 50.0f)); // Set the size of the enemy
    body.setTexture(texture); // Set the texture
}
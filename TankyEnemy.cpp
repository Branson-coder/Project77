#include "TankyEnemy.h"

TankyEnemy::TankyEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
    : Enemy(texture, imageCount, 2.0f, 200.0f, 2.0f) {

    body.setSize(sf::Vector2f(100.0f, 100.0f)); // Set the size of the enemy
    body.setTexture(texture); // Set the texture
}

void TankyEnemy::update(float deltaTime, const Player& player)
{
    
float xDif = player.GetPosition().x - body.getPosition().x;
float yDif = player.GetPosition().y - body.getPosition().y;
row = 0;

movement = sf::Vector2f(0.0f, 0.0f);

//up
if (yDif < 0 && std::abs(yDif) > std::abs(xDif)) {
  direction = sf::Vector2f(0.0f, -1.0f);
  movement.y -= speed * deltaTime;
  row = 3;
		
    }//right
    else if (xDif > 0 && std::abs(xDif) > std::abs(yDif)) {
        direction = sf::Vector2f(1.0f, 0.0f);
        movement.x += speed * deltaTime;
		row = 2;
		
    }//left
    else if (xDif < 0 && std::abs(xDif) > std::abs(yDif)) {
        direction = sf::Vector2f(-1.0f, 0.0f);
        movement.x -= speed * deltaTime;
		row = 1;
		
    }//down
    else if (yDif > 0 && std::abs(yDif) > std::abs(xDif)) {
        direction = sf::Vector2f(0.0f, 1.0f);
        movement.y += speed * deltaTime;
		row = 0;
		
    }

        animation.Update(row, deltaTime);
        body.setTextureRect(animation.uvRect);
        body.move(movement);
}

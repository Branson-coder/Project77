#include "Enemy.h"
Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f spawnPos, Projectile projectile, float switchTime, int type) 
            : animation(texture, imageCount, switchTime)
{
    active = false;
    speed = 200.0f;
    currentSpeed = speed;
    enemyProjectile = projectile;

    timeDelay = 0;
    row = 0;
    faceRight = true;
    damage = 10;
    
    
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);

}

void Enemy::update(float deltaTime, Player player)
{
	float xDif = player.GetPosition().x - body.getPosition().x;
	float yDif = player.GetPosition().y - body.getPosition().y;
	timeDelay += deltaTime;

    if (active)
    {
        movement = sf::Vector2f(0.0f, 0.0f);

        // if player is above enemy
        if (yDif < -100 && abs(yDif) > abs(xDif))
			{
				direction = sf::Vector2f(0.0f, -1.0f);
				movement.y -= currentSpeed * deltaTime;
			}
			//if player is to the right of enemy
			else if (xDif > 100 && abs(xDif) > abs(yDif))
			{
				direction = sf::Vector2f(1.0f, 0.0f);
				movement.x += currentSpeed * deltaTime;

			}
			//if player is to the left of enemy
			else if (xDif < -100 && abs(xDif) > abs(yDif))
			{
				direction = sf::Vector2f(-1.0f, 0.0f);
				movement.x -= currentSpeed * deltaTime;
			}
			//if player is below enemy
			else if (yDif > 100 && abs(yDif) > abs(xDif))
			{
				direction = sf::Vector2f(0.0f, 1.0f);
				movement.y += currentSpeed * deltaTime;
			}
            
			else if (movement.x != 0)
			{
				row = 1;
				if (movement.x > 0.0f)
				{
					faceRight = true;
				}
				else
				{
					faceRight = false;
				}
			}
			else if (movement.y != 0)
			{
				if (movement.y > 0.0f)
				{
					row = 2;
					faceUp = true;
				}
				else
				{
					row = 4;
					faceUp = false;
				}
			}
		

    }

}



void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(body);
}


void Enemy::setActive()
{
	active = true;
}

Enemy::~Enemy()
{
}
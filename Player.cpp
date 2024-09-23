#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,
               float speed)
    : animation(texture, imageCount, switchTime), body(), collider(body)
{
  this->speed = speed;
  row = 0;

  body.setSize(sf::Vector2f(50.0f, 70.0f));
  body.setOrigin(body.getSize() / 2.0f);
  body.setPosition(206.0f, 206.0f);
  body.setTexture(texture);

}

Player::~Player() {}

void Player::Update(float deltaTime) 
{
    sf::Vector2f movement(0.0f, 0.0f);

        isMoving = false;    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // Move Left
    {
        movement.x -= speed * deltaTime;
        row = 2;
        isMoving = true;
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // Move Right
    {
        movement.x += speed * deltaTime;
        row = 3;
        isMoving = true;
        
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  // Move Up
    {
        movement.y -= speed * deltaTime;
        row = 1;
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // Move Down
    {
        movement.y += speed * deltaTime;
        row = 0;
        isMoving = true;
    }

    if (isMoving) 
    {
        animation.Update(row, deltaTime);
        body.setTextureRect(animation.uvRect);
        body.move(movement);
         
    }
    else
    {
        row = 0;
        animation.ResetCurrentImage();
        body.setTextureRect(animation.uvRect); 
    }
    
}

void Player::Draw(sf::RenderWindow &window) 
{
    window.draw(body);
}
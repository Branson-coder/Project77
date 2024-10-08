#include <iostream>
#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
    : animation(texture, imageCount, switchTime), currentWeapon(nullptr)
{
    this->speed = speed;
    row = 0;
    timeDelay = 0.0f;
    health = 100.0f;  // Initialize player's health

    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);

    // Default to facing down initially
    facingDirection = Down;

}

Player::~Player() {
    if(currentWeapon != nullptr)  {
        delete currentWeapon;
        currentWeapon = nullptr;
    }
    
}

void Player::equipWeapon(Weapon* weapon) {
    if (weapon) {
        inventory.push_back(weapon);
        std::cout << "Weapon is in to inventory." << std::endl; //text to check for now
        if (currentWeapon == nullptr) {
            currentWeapon = weapon;  
            std::cout << "Equipped weapon." << std::endl;
        }
    }
}

void Player::shoot() {
    if (currentWeapon) {
        sf::Vector2f direction;
        sf::Vector2f playerPosition = body.getPosition();
        sf::FloatRect playerBounds = body.getGlobalBounds();
        sf::Vector2f playerSize(playerBounds.width, playerBounds.height);

        switch (facingDirection) {
            case Left:  direction = sf::Vector2f(-1.0f, 0.0f); break;
            case Right: direction = sf::Vector2f(1.0f, 0.0f); break;
            case Up:    direction = sf::Vector2f(0.0f, -1.0f); break;
            case Down:  direction = sf::Vector2f(0.0f, 1.0f); break;
        }

        sf::Vector2f spawnPosition = playerPosition;
        
 switch (facingDirection) {
            case Left:  
                spawnPosition.x -= playerSize.x / 2; 
                spawnPosition.y += playerSize.y / 2; 
                break;
            case Right: 
                spawnPosition.x += playerSize.x / 2; 
                spawnPosition.y -= playerSize.y / 2; 
                break;
            case Up:    
                spawnPosition.x -= playerSize.x / 2; 
                spawnPosition.y -= playerSize.y / 2;
                break;
            case Down:  
                spawnPosition.x += playerSize.x / 2; 
                spawnPosition.y += playerSize.y / 2;
                break;
        }
        currentWeapon->fire(direction, spawnPosition);
    }
    else {
        std::cout << "No weapon equipped!" << std::endl;
    }
}

void Player::Update(float deltaTime, const sf::RenderWindow& window)
{
    sf::Vector2f movement(0.0f, 0.0f);
    bool isMoving = false;
    timeDelay += deltaTime;

    // Update player movement and track facing direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // Move Left
    {
        movement.x -= speed * deltaTime;
        row = 2;
        facingDirection = Left;  // Player is now facing left
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // Move Right
    {
        movement.x += speed * deltaTime;
        row = 3;
        facingDirection = Right;  // Player is now facing right
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  // Move Up
    {
        movement.y -= speed * deltaTime;
        row = 1;
        facingDirection = Up;  // Player is now facing up
        isMoving = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // Move Down
    {
        movement.y += speed * deltaTime;
        row = 0;
        facingDirection = Down;  // Player is now facing down
        isMoving = true;
    }


    // Move the player
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

    if (currentWeapon) {
        currentWeapon->updateProjectiles(deltaTime, window);
    }
}


void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
     if (currentWeapon) {
        currentWeapon->drawProjectiles(window);
    }
}


void Player::takeDamage(float damage) // should be enemy damage here
{
    health -= damage;  // Decrease health by damage amount
    if (health < 0) {
        health = 0;  // Clamp health to zero
    }

    
}

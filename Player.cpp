// this is the player class, responsible for animation of player, movement,
// collecting items and being the main holder of many objects such as health
// potions, guns, etc.
#include "Player.h"

#include <iostream>

using namespace std;

// constructor
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,
               float speed)
    : animation(texture, imageCount, switchTime),
      currentWeapon(nullptr),
      healCount(0) {
  this->speed = speed;
  row = 0;
  timeDelay = 0.0f;
  health = 100.0f;
  score = 0;

  body.setSize(sf::Vector2f(70.0f, 70.0f));
  body.setOrigin(body.getSize() / 2.0f);
  body.setPosition(206.0f, 206.0f);
  body.setTexture(texture);

  // face down initially
  facingDirection = Down;
}

// destructor
Player::~Player() {
  if (currentWeapon != nullptr) {
    delete currentWeapon;
    currentWeapon = nullptr;
  }
}

// equip weapon function with debugging message
void Player::equipWeapon(Weapon* weapon) {
  if (weapon) {
    std::cout << "Equipping new weapon" << std::endl;
    currentWeapon = weapon;
  }
}

// shoot function
void Player::shoot() {
  if (currentWeapon) {
    sf::Vector2f direction;
    sf::Vector2f playerPosition = body.getPosition();
    sf::FloatRect playerBounds = body.getGlobalBounds();
    sf::Vector2f playerSize(playerBounds.width, playerBounds.height);

    //direction that player is facing
    switch (facingDirection) {
      case Left:
        direction = sf::Vector2f(-1.0f, 0.0f);
        break;
      case Right:
        direction = sf::Vector2f(1.0f, 0.0f);
        break;
      case Up:
        direction = sf::Vector2f(0.0f, -1.0f);
        break;
      case Down:
        direction = sf::Vector2f(0.0f, 1.0f);
        break;
    }

    sf::Vector2f spawnPosition =
        playerPosition;  // spawn bullets from the player position

    // bullets fire according to the direction that the player is facing
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
  } else {
    std::cout << "No weapon equipped!" << std::endl;
  }
}

Weapon* Player::getCurrentWeapon() { return currentWeapon; }

//update the player's position according to the user inputs
void Player::Update(float deltaTime, const sf::RenderWindow& window) {
  sf::Vector2f movement(0.0f, 0.0f);
  bool isMoving = false;
  timeDelay += deltaTime;

  // player movement and facing direction
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))  // Left
  {
    movement.x -= speed * deltaTime;
    row = 2;
    facingDirection = Left;  // player is now facing left
    isMoving = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))  // Right
  {
    movement.x += speed * deltaTime;
    row = 3;
    facingDirection = Right;  // player is now facing right
    isMoving = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))  // Up
  {
    movement.y -= speed * deltaTime;
    row = 1;
    facingDirection = Up;  // player is now facing up
    isMoving = true;
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))  // Down
  {
    movement.y += speed * deltaTime;
    row = 0;
    facingDirection = Down;  // Player is now facing down
    isMoving = true;
  }

  // move and animate the player according to isMoving boolean
  if (isMoving) {
    animation.Update(row, deltaTime);
    body.setTextureRect(animation.uvRect);
    body.move(movement);
  } else { //player is a non-stationary image
    row = 0;
    animation.ResetCurrentImage();
    body.setTextureRect(animation.uvRect);
  }

  if (currentWeapon) {
    currentWeapon->updateProjectiles(deltaTime, window);
  }
}

void Player::Draw(sf::RenderWindow& window) {
  window.draw(body);
  if (currentWeapon) {
    currentWeapon->drawProjectiles(window);
  }
}

void Player::takeDamage(float damage)  
{
  health -= damage;  
  if (health < 0) {
    health = 0; 
    gameOver();
  }
}

bool Player::equipHeal(Heals* heal) {
  if (healCount < 5) {  // checks if there is space in the inventory
    healInventory[healCount] = heal;
    healCount++;
    std::cout << "Heals added to inventory. Current heal count: " << healCount
              << std::endl; //debugging message
    return true;  // equipped the heal
  } else {
    std::cout << "Cannot equip more heals" << std::endl;
    return false;  // inventory is full and so player cannot equip the heal
  }
}

int Player::getHealthPotionCount() { return healCount; }

float Player::getHealth() const { return health; }

void Player::setHealth(float newHealth) {
  if (newHealth > 100.0f) {
    health = 100.0f;  // max health at 100
  } else if (newHealth < 0.0f) {
    health = 0.0f;  // health should not be below 0
  } else {
    health = newHealth;
  }
}

void Player::useHeal() {
  if (healCount > 0) {
    if (getHealth() >= 100.0f) {
      std::cout << "Health is already full! Cannot use heal." << std::endl; //debugging message
      return;
    }

    float newHealth = getHealth() + 20.0f; // add 20 points to health
    setHealth(newHealth);

    healInventory[healCount - 1] = nullptr;
    healCount--;

    std::cout << "Heals remaining: " << healCount << std::endl;
  } else {
    std::cout << "No heals available in the inventory!" << std::endl;
  }
}

int Player::getAmmo() {
  if (currentWeapon) {
    return currentWeapon->getAmmo();  // Return ammo from the equipped weapon
  } else {
    return 0;  // No weapon equipped, return 0 ammo
  }
}

int Player::getScore() { return score; }

void Player::gameOver() { std::cout << "Game Over!" << std::endl; }
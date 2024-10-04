#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
    : animation(texture, imageCount, switchTime)
{
    this->speed = speed;
    row = 0;
    timeDelay = 0.0f;

    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);

    // Default to facing down initially
    facingDirection = Down;

    projectileTexture.loadFromFile("Projectile.png");

}

Player::~Player() {}

void Player::Update(float deltaTime)
{
    sf::Vector2f movement(0.0f, 0.0f);
    isMoving = false;
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

   // Fire a projectile in the direction the player is facing
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timeDelay > 0.5f)  // Fire every 0.5 seconds
    {
        timeDelay = 0;  // Reset fire timer

        sf::Vector2f projectileDirection;
        float rotationAngle = 0.0f;  // Variable to store the angle for projectile rotation
        sf::Vector2f playerPosition = body.getPosition();
        
        sf::Vector2f projectileSpawnPosition = playerPosition;

        switch (facingDirection)
        {
            case Left: 
                projectileDirection = sf::Vector2f(-1.0f, 0.0f); 
                rotationAngle = 180.0f;  // Rotate 180 degrees to face left
                projectileSpawnPosition.x += body.getSize().x/5;
                projectileSpawnPosition.y += body.getSize().y/2;
                break;

            case Right: 
                projectileDirection = sf::Vector2f(1.0f, 0.0f); 
                rotationAngle = 0.0f;  // Default rotation (facing right)
                projectileSpawnPosition.x -= body.getSize().x/5;
                projectileSpawnPosition.y -= body.getSize().y/2;
                break;

            case Up: 
                projectileDirection = sf::Vector2f(0.0f, -1.0f); 
                rotationAngle = 270.0f;  // Rotate 270 degrees to face up
                projectileSpawnPosition.x -= body.getSize().x/2;
                projectileSpawnPosition.y += body.getSize().y/5;
                break;

            case Down: 
                projectileDirection = sf::Vector2f(0.0f, 1.0f); 
                rotationAngle = 90.0f;  // Rotate 90 degrees to face down
                projectileSpawnPosition.x += body.getSize().x/2;
                projectileSpawnPosition.y -= body.getSize().y/5;
                break;
        }

        Projectile newProjectile(&projectileTexture, projectileSpawnPosition, projectileDirection, 500.0f);
        newProjectile.setRotation(rotationAngle);  // Set the projectile's rotation
        projectiles.push_back(newProjectile);
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

    // Update projectiles
    updateProjectiles(deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);

    // Draw projectiles
    drawProjectiles(window);
}

void Player::drawProjectiles(sf::RenderWindow& window)
{
    for (auto& proj : projectiles)
    {
        proj.Draw(window);
    }
}

void Player::updateProjectiles(float deltaTime)
{
    for (int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].Update(deltaTime);
    }

    // Remove projectiles that have expired or are out of bounds
    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
                                     [](Projectile& p) { return p.getLifetime() <= 0; }),
                      projectiles.end());
}

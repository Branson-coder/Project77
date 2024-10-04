#include "Projectile.h"
#include <cmath>

Projectile::Projectile(sf::Texture* texture, sf::Vector2f startPosition, sf::Vector2f direction, float speed)
{
    this->speed = speed;
    this->lifetime = 500;  // Set a default lifetime for the projectile
    body.setTexture(*texture);
    body.setPosition(startPosition);
    body.setScale(0.05f, 0.05f);  // Scale down the texture if it's too large

    // Normalize direction to ensure consistent speed
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude != 0)
    {
        direction /= magnitude;  // Ensure direction is a unit vector
    }
    
    velocity = direction * speed;
}

void Projectile::Update(float deltaTime)
{
    // Move the projectile based on velocity and deltaTime
    body.move(velocity * deltaTime);
    
    // Decrease lifetime each frame
    lifetime--;
}

void Projectile::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

bool Projectile::isOffScreen(const sf::RenderWindow& window)
{
    sf::Vector2f position = body.getPosition();
    return (position.x < 0 || position.x > window.getSize().x || position.y < 0 || position.y > window.getSize().y);
}

void Projectile::setStartDirection(sf::Vector2f startDirection)
{
    // Normalize startDirection and set velocity
    float magnitude = sqrt(startDirection.x * startDirection.x + startDirection.y * startDirection.y);
    if (magnitude != 0)
    {
        startDirection /= magnitude;
    }
    velocity = startDirection * speed;
}

void Projectile::setRotation(float angle)
{
    body.setRotation(angle);  // Rotate the projectile sprite
}

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Collider.h"

class Projectile
{
public:
    Projectile(sf::Texture* texture, sf::Vector2f startPosition, sf::Vector2f size, sf::Vector2f direction, float speed);

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);
    bool isOffScreen(const sf::RenderWindow& window);

    int getLifetime() { return lifetime; }
    void setStartDirection(sf::Vector2f startDirection);
    void setRotation(float angle);  // Function to rotate the projectile
    Collider GetCollider() {
        return Collider(body);
    }
protected:
    sf::RectangleShape body;
    sf::Vector2f velocity;
    float speed;
    int lifetime;  // Used to limit how long the projectile exists
};

#endif

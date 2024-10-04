#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Animation.h"
#include "Collider.h"
#include "Projectile.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f GetPosition() { return body.getPosition(); }
    Collider GetCollider() { return Collider(body); }

    void drawProjectiles(sf::RenderWindow& window);
    void updateProjectiles(float deltaTime);

private:
    enum Direction { Up, Down, Left, Right };
    Direction facingDirection;

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool isMoving;
    float timeDelay;

    // Store projectiles
    sf::Texture projectileTexture;
    std::vector<Projectile> projectiles;
};

#endif

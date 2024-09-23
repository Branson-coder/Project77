#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
    public:
        Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
        ~Player();

        void Update(float deltaTime);
        void Draw(sf::RenderWindow &window);

        sf::Vector2f GetPosition(){return body.getPosition();}
        Collider& GetCollider(){return collider;}

    private:
     sf::RectangleShape body;
     Animation animation;
     unsigned int row;
     float speed;
     bool isMoving;
     Collider collider;


};

#endif
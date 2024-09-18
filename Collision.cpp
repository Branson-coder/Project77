#include "Collision.h"
#include <SFML/Graphics.hpp>

Collision::Collision(sf::RectangleShape& body):body(body){}

//checks collision using AABB method 
bool Collision::checkCollision(Collision& other, float push)
{   sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();

    float diffX = otherPosition.x - thisPosition.x;
    float diffY = otherPosition.y - thisPosition.y;

    float intersectX = abs(diffX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(diffY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0f && intersectY< 0.0f ){ //proceed with collision response
        return true;
    }

    return false; 
}
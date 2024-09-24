#include "Collider.h"
#include <SFML/Graphics.hpp>

Collider::Collider(sf::RectangleShape& body):body(body){}

//checks collision using AABB method 
bool Collider::checkCollision(Collider& other, float push)
{   sf::Vector2f otherPosition = other.GetPosition();
    sf::Vector2f otherHalfSize = other.GetHalfSize();
    sf::Vector2f thisPosition = GetPosition();
    sf::Vector2f thisHalfSize = GetHalfSize();
    

    float diffX = otherPosition.x - thisPosition.x;
    float diffY = otherPosition.y - thisPosition.y;

    float intersectX = abs(diffX) - (thisHalfSize.x + otherHalfSize.x);
    float intersectY = abs(diffY) - (thisHalfSize.y + otherHalfSize.y);

    if(intersectX < 0.0f && intersectY< 0.0f ){ //proceed with collision response
  
      if(intersectX > intersectY){ 
        if(diffX > 0.0f){
            Move(intersectX * (1.0f - push), 0.0f);
            other.Move(-intersectY * push, 0.0f);
        }
        else{
            Move(-intersectX * (1.0f - push), 0.0f);
            other.Move(intersectY * push, 0.0f);
        }
      }   
      else{ 
        if(diffY > 0.0f){
            Move(0.0f, intersectY * (1.0f - push));
            other.Move(0.0f, -intersectX * push);
        }
        else{
            Move(0.0f, -intersectY * (1.0f - push));
            other.Move(0.0f, intersectX * push);
        }
      }

        return true;
    }

    return false; 
}
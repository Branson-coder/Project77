#include <SFML/Graphics.hpp>
#ifndef COLLISION_H
#define COLLISION_H

class Collider{
private:
    sf::RectangleShape& body;
public:
    Collider(sf::RectangleShape& body);
    void Move(float dx, float dy){body.move(dx,dy);}; // to move objects by a certain direction
    bool checkCollision(Collider& other, float push);
   
    // following AABB collision detection
    sf::Vector2f GetPosition(){return body.getPosition();} 
    sf::Vector2f GetHalfSize(){return body.getSize()/2.0f;}


};

#endif
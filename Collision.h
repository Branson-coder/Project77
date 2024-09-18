#include <SFML/Graphics.hpp>
#ifndef COLLISION_H
#define COLLISION_H

class Collision{
private:
    sf::RectangleShape& body;
public:
    Collision(sf::RectangleShape& body);
    ~Collision();
    void move(float dx, float dy){body.move(dx,dy);}; // to move objects by a certain direction
    bool checkCollision(Collision& other, float push);
   
    // following AABB collision detection
    sf::Vector2f GetPosition(){return body.getPosition();} 
    sf::Vector2f GetHalfSize(){return body.getSize()/2.0f;}


};

#endif
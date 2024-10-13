//header file for fast enemy classm which inherits from enemy class
#ifndef FASTENEMY_H
#define FASTENEMY_H

#include "Enemy.h"

class FastEnemy : public Enemy 
{
public:
    //constructor
    FastEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);

    //update function which has been overridden from enemy
    void update(float deltaTime, const Player& player) override;

};

#endif 

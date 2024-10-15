//header file for normal enemy
#ifndef NORMALENEMY_H
#define NORMALENEMY_H
#include "Enemy.h"

class NormalEnemy : public Enemy
{

    public:
    NormalEnemy(sf::Texture* texture, sf::Vector2u imageCount); 

    void update(float deltaTime, const Player& player) override;
    

};


#endif
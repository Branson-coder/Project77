//header file for tanky enemy class
#ifndef TANKYENEMY_H
#define TANKYENEMY_H
#include "Enemy.h"

class TankyEnemy : public Enemy
{
    public:
    TankyEnemy(sf::Texture* texture, sf::Vector2u imageCount); //constructor

   void update(float deltaTime, const Player& player) override; //overridden from enemy class
};

#endif
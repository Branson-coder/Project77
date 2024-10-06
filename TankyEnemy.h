#ifndef TANKYENEMY_H
#define TANKYENEMY_H
#include "Enemy.h"

class TankyEnemy : public Enemy
{
    private:



    public:
    TankyEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);  // lower speed, higher health

   void update(float deltaTime, const Player& player) override;
};

#endif
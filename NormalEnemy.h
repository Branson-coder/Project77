#ifndef NORMALENEMY_H
#define NORMALENEMY_H
#include "Enemy.h"

class NormalEnemy : public Enemy
{
    private:


    public:
    NormalEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);  // normal speed, normal health

    void update(float deltaTime, const Player& player) override;
    


};


#endif
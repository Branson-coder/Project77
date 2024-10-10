#ifndef FASTENEMY_H
#define FASTENEMY_H

#include "Enemy.h"

class FastEnemy : public Enemy 
{
public:
    FastEnemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);  // Higher speed, lower health

    void update(float deltaTime, const Player& player) override;

};

#endif 

#ifndef PUMP_H
#define PUMP_H
#include "Shotgun.h"

// Base class for the pump weapon
class Pump : public Shotgun {
public:
    // Constructor
    Pump(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex);

    // Override the fire function
    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
};

#endif
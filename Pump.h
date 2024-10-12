#ifndef PUMP_H
#define PUMP_H
#include "Shotgun.h"

class Pump : public Shotgun {
public:
    Pump(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex, const std::string& name);

    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
};

#endif
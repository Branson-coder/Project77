#ifndef SAWEDOFF_H
#define SAWEDOFF_H
#include "Shotgun.h"

class SawedOff : public Shotgun {
public:
    SawedOff(sf::Texture* texture, sf::Vector2f size, sf::Texture* projectileTex, const std::string& name);

    void fire(sf::Vector2f direction, sf::Vector2f startPosition) override;
};

#endif
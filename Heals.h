//this header file contains the heals class
#ifndef HEALS_H
#define HEALS_H

#include "Item.h"

class Heals : public Item {

public:
    // constructor
    Heals(sf::Vector2f position, sf::Texture* texture);

    // override the effect function in items class
    void effect() override;

    ~Heals() override;
};


#endif // HEALS_H
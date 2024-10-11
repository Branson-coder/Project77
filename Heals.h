#ifndef HEALS_H
#define HEALS_H

#include "Item.h"

class Heals : public Item {

public:
    // Constructor
    Heals(sf::Vector2f position, sf::Texture* texture);

    // Override the effect function
    void effect() override;
};


#endif // HEALS_H
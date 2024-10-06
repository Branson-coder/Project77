#ifndef AMMO_H
#define AMMO_H

#include "Item.h"

class Ammo : public Item {
private:
    int ammoCount;

public:
    Ammo(sf::Vector2f position, const std::string& type, int ammoCount);

    void effect() override;

    void Draw(sf::RenderWindow& window) override;
};

#endif
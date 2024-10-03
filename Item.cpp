#include "Item.h"

Item::Item(sf::Vector2f position, std::string& type) {
    this->itemPosition = position;
    this->itemType = type;
    this->isPickedUp = false; 

    shape.setPosition(position);
}

void Item::collect() {
    this->isPickedUp = true;
}

sf::Vector2f Item::getPosition() {
    return this->itemPosition;
}

bool Item::getIsPickedUp() {
    return this->isPickedUp;
}

void Item::Draw(sf::RenderWindow& window) {
    if (isPickedUp = false) {
        window.draw(shape);
    }
}
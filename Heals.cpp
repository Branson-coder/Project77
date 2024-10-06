#include "Heals.h"
#include <iostream>

// Constructor
Heals::Heals(sf::Vector2f position, sf::Texture* texture)
    : Item(position, "Healing Item") // Call base class constructor
{
    shape.setTexture(texture); 
    shape.setSize(sf::Vector2f(60.0f, 60.0f)); 
    shape.setPosition(position); 
}


// Override the effect function
void Heals::effect() 
{
    // Implement healing effect, for example, restore player's health
    std::cout << "Player healed!" << std::endl; 
}
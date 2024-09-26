#include "Wall.h"
#include <SFML/Graphics.hpp>

Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, sf::Color colour, bool hasCollided) 
{
	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);
	body.setFillColor(colour);
	this -> hasCollided = hasCollided;
}

Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
#include "Wall.h"
#include <SFML/Graphics.hpp>

Wall::Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position): body(size), collider(body)
{
	body.setSize(size);
	body.setPosition(position);
	body.setTexture(texture);
	body.setOrigin(size / 2.0f);

}

Wall::~Wall()
{
}

void Wall::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}
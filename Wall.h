#ifndef WALL_H
#define WALL_H
#include "SFML/Graphics.hpp"
#include "Collider.h"
class Wall
{
public:
	Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, bool hasCollided);
	~Wall();

	void Draw(sf::RenderWindow& window);

	Collider GetCollider()
	{
		return Collider(body);
	}

	sf::RectangleShape getBody()
	{
		return body;
	}

	bool getColliderState(){return hasCollided;}

private:
	sf::RectangleShape body;
	bool hasCollided;


};
#endif
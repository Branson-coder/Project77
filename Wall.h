#include "SFML/Graphics.hpp"
#include "Collider.h"
class Wall
{
public:
	Wall(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Wall();

	void Draw(sf::RenderWindow& window);

	Collider& GetCollider()
	{
		return collider;
	}

	sf::RectangleShape getBody()
	{
		return body;
	}

	bool getcolliderState()
	{
		return hasCollider;
	}

private:
	sf::RectangleShape body;
	bool hasCollider;
	Collider collider;

};

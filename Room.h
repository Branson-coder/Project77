#include <random>
#include "Wall.h"
#include "Player.h"
#include <vector>
using namespace std;

class Room
{
public:
	Room(sf::Texture* texture, sf::Vector2f position, int roomType);
    void Display(sf::RenderWindow & window, Collider playerCollider, Player &player);
	void Exits(sf::Texture* texture, int roomType);
	void miniMap(sf::RenderWindow & window);
	Room();
	~Room();


    private:
	vector<vector<Wall>> layout;
	sf::Vector2f maxSize = sf::Vector2f(15.0f,9.0f);
	sf::Vector2f center;
	float xBound1;
	float xBound2;
	float yBound1;
	float yBound2;

};

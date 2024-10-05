#include <random>
#include "Wall.h"
#include "Player.h"
#include "Weapon.h"
#include <vector>
using namespace std;

class Room
{
public:
	Room(sf::Texture* texture, sf::Vector2f position, int roomType);
    void Display(sf::RenderWindow & window, Collider playerCollider, Player &player);
	void generateWeapons();
	Room();



    private:
    vector<Weapon*> weapons;
	vector<vector<Wall>> layout;
	sf::Vector2f maxSize = sf::Vector2f(15.0f,9.0f);

	
};

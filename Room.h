#include <random>
#include "Wall.h"
#include "Player.h"
#include "Weapon.h"
#include "AK47.h"
#include "FastEnemy.h"
#include "TankyEnemy.h"
#include "NormalEnemy.h"
#include <vector>
#include "Heals.h"
#include "Ammo.h"
using namespace std;

class Room
{
public:
	Room(sf::Texture* texture, sf::Vector2f position, int roomType);
    void Display(sf::RenderWindow & window, Collider playerCollider, Player &player, float deltaTime);
	
	void generateWeapons();
	void spawnFastEnemies();
	void spawnTankyEnemies();
	void spawnNormalEnemies();
	void generateHeals();

	~Room();



    private:
    vector<Weapon*> weapons;
	vector<vector<Wall>> layout;
	sf::Vector2f maxSize = sf::Vector2f(15.0f,9.0f);
	std::vector<Enemy*> enemies;
	std::vector<Heals*> healthPacks;

};

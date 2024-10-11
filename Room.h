#include <random>
#include <vector>

#include "AK47.h"
#include "M16.h"
#include "Ammo.h"
#include "FastEnemy.h"
#include "Heals.h"
#include "Item.h"
#include "NormalEnemy.h"
#include "Player.h"
#include "SawedOff.h"
#include "TankyEnemy.h"
#include "Wall.h"
#include "Weapon.h"
#include "LaserGun.h"
using namespace std;

class Room {
 public:
  Room(sf::Texture* texture, sf::Vector2f position, int roomType);
  void Display(sf::RenderWindow& window, Collider playerCollider,
               Player& player, float deltaTime);

  void generateWeapons();
  void spawnFastEnemies();
  void spawnTankyEnemies();
  void spawnNormalEnemies();
  void generateHeals();

  ~Room();
  void update();

 private:
  vector<Weapon*> weapons;
  vector<vector<Wall>> layout;
  sf::Vector2f maxSize = sf::Vector2f(15.0f, 9.0f);
  std::vector<Enemy*> enemies;
  std::vector<Heals*> healthPacks;
  sf::Clock enemySpawnClock;  // Clock to track enemy spawn timing
  sf::Time spawnInterval;     // Time interval for spawn
  sf::Clock itemSpawnClock; //time interval for item spawn timing

};

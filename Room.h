#ifndef ROOM_H
#define ROOM_H
#include <random>
#include <vector>

#include "AK47.h"
#include "FastEnemy.h"
#include "Heals.h"
#include "Item.h"
#include "LaserGun.h"
#include "M16.h"
#include "NormalEnemy.h"
#include "Player.h"
#include "Pump.h"
#include "SawedOff.h"
#include "TankyEnemy.h"
#include "Wall.h"
#include "Weapon.h"
using namespace std;

class Room {
 public:
  Room(sf::Texture* texture, sf::Vector2f position);
  void Display(sf::RenderWindow& window, Collider playerCollider,
               Player& player, float deltaTime);

  void generateWeapons();
  void spawnFastEnemies();
  void spawnTankyEnemies();
  void spawnNormalEnemies();
  void generateHeals();

  static const float VIEW_HEIGHT;
  void ResizeView(const sf::RenderWindow& window, sf::View& view);

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
  sf::Clock itemSpawnClock;   // time interval for item spawn timing
};

#endif
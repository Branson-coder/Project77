#include "Room.h"

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

using namespace std;

Room::Room(sf::Texture* texture, sf::Vector2f position)
    : spawnInterval(sf::seconds(5)) {
  for (int x = 0; x < maxSize.x; x++) {
    layout.push_back(vector<Wall>());
    for (int y = 0; y < maxSize.y; y++) {
      if (x == 0 || x == maxSize.x - 1 || y == 0 || y == maxSize.y - 1 ||
          y == 0) {
        layout[x].push_back(
            Wall(texture, sf::Vector2f(100.0f, 100.f),
                 position + sf::Vector2f(100.0f * x, 100.0f * y),
                 sf::Color::White, true));

      } else {
        layout[x].push_back(
            Wall(nullptr, sf::Vector2f(100.0f, 100.f),
                 position + sf::Vector2f(100.0f * x, 100.0f * y),
                 sf::Color::Black, false));
      }
    }
  }
}

Room::~Room() {
  for (Enemy* enemy : enemies) {
    delete enemy;  // Free memory for each enemy
  }
  enemies.clear();
  for (Weapon* weapon : weapons) {
    delete weapon;  // Free memory for each weapon
  }
  weapons.clear();

  for (Heals* healthPack : healthPacks) {
    delete healthPack;  // Free memory for each healthpack
  }
  healthPacks.clear();
}

void Room::generateWeapons() {
  static sf::Texture akTexture;
  static bool akTextureLoaded = false;
  if (!akTextureLoaded) {
    if (!akTexture.loadFromFile("AK47.png")) {
      std::cerr << "Error loading AK47 texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    akTextureLoaded = true;
  }

  static sf::Texture M16Texture;
  static bool m16TextureLoaded = false;
  if (!m16TextureLoaded) {
    if (!M16Texture.loadFromFile("M16.png")) {
      std::cerr << "Error loading M16 texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    m16TextureLoaded = true;
  }

  static sf::Texture shotTexture;
  static bool shotTextureLoaded = false;
  if (!shotTextureLoaded) {
    if (!shotTexture.loadFromFile("SawedOff.png")) {
      std::cerr << "Error loading Sawed Off texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    shotTextureLoaded = true;
  }

  static sf::Texture pumpTexture;
  static bool pumpTextureLoaded = false;
  if (!pumpTextureLoaded) {
    if (!pumpTexture.loadFromFile("Pump.png")) {
      std::cerr << "Error loading Pump texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    pumpTextureLoaded = true;
  }

  static sf::Texture projectileTex;
  static bool projectileTexLoaded = false;
  if (!projectileTexLoaded) {
    if (!projectileTex.loadFromFile("Projectile.png")) {
      std::cerr << "Error loading projectile texture!" << std::endl;
      return;
    }
    projectileTexLoaded = true;
  }

  static sf::Texture laserGunTexture;
  static bool laserTextureLoaded = false;
  if (!laserTextureLoaded) {
    if (!laserGunTexture.loadFromFile("LaserGun.png")) {
      std::cerr << "Error loading laser gun texture!"
                << std::endl;  // debugging stuff just in case
      return;
    }
    laserTextureLoaded = true;
  }

  static sf::Texture laserTex;  // Texture for the laser beam
  static bool laserTexLoaded =
      false;  // Flag to check if the laser texture is loaded

  if (!laserTexLoaded) {
    if (!laserTex.loadFromFile(
            "Laser.png")) {  // Ensure you have the correct file name and path
      std::cerr << "Error loading laser texture!" << std::endl;
      return;
    }
    laserTexLoaded = true;  // Set the flag to true once loaded
  }

  // Randomises randomWeaponType value between numbers 0-4
  int randomWeaponType = rand() % 5;

  // Switch statement to select a random weapon with corresponding
  // randomWeaponType number
  switch (randomWeaponType) {
    case 0:
      // The loop iterates once to provide a scope for the variables
      // Randomises position of weapon within maxSize bounds and not on the edge
      for (int i = 0; i < 1; i++) {
        float x =
            static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y =
            static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")"
                  << std::endl;

        // Create a new AK47 weapon and store it as newWeapon pointer
        Weapon* newWeapon =
            new AK47(&akTexture, sf::Vector2f(50.0f, 30.0f), projectileTex);

        // Set the position of the newly created weapon
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));

        // Adds the AK47 into the weapon list
        weapons.push_back(newWeapon);
      }
      break;

    // Case 1: spawning SawedOff weapon
    case 1:
      // Creates new SawedOff weapon at randomised positions
      for (int i = 0; i < 1; i++) {
        float x =
            static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y =
            static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")"
                  << std::endl;

        Weapon* newWeapon = new SawedOff(
            &shotTexture, sf::Vector2f(50.0f, 30.0f), &projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);
      }
      break;

    // Case 2: spawning M16 weapon
    case 2:
      for (int i = 0; i < 1; i++) {
        float x =
            static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y =
            static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")"
                  << std::endl;

        Weapon* newWeapon =
            new M16(&M16Texture, sf::Vector2f(50.0f, 30.0f), projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);
      }
      break;

    // Case 3: spawning Pump weapon
    case 3:
      for (int i = 0; i < 1; i++) {
        float x =
            static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y =
            static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")"
                  << std::endl;

        Weapon* newWeapon =
            new Pump(&pumpTexture, sf::Vector2f(70.0f, 50.0f), &projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);
      }
      break;

    // Case 4: spawning lasergun weapon
    case 4:
      for (int i = 0; i < 1; i++) {
        float x =
            static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y =
            static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")"
                  << std::endl;

        Weapon* newWeapon =
            new LaserGun(&laserGunTexture, sf::Vector2f(100.0f, 80.0f),
                         laserTex, "LaserGun");
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);
      }
      break;
  }
}

void Room::generateHeals() {
  static sf::Texture healTexture;
  static bool healTextureLoaded = false;
  if (!healTextureLoaded) {
    if (!healTexture.loadFromFile("heal.png")) {
      std::cerr << "Error loading heal.png texture!" << std::endl;
      return;
    }
    healTextureLoaded = true;
  }

  for (int i = 0; i < 1; i++) {
    float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
    float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
    std::cout << "Spawning health pack at: (" << x << ", " << y << ")"
              << std::endl;

    // Dynamically allocate the health pack
    Heals* newHealthPack =
        new Heals(sf::Vector2f(100.0f * x, 100.0f * y), &healTexture);
    healthPacks.push_back(newHealthPack);
  }
}

void Room::ResizeView(const sf::RenderWindow& window, sf::View& view) {
  float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
  view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

void Room::update() {
  // Update enemy spawning
  if (enemySpawnClock.getElapsedTime() >= spawnInterval) {
    int randomEnemyType = rand() % 9;  // rand choose an enemy type

    switch (randomEnemyType) {
      case 0:
        spawnFastEnemies();
        break;
      case 1:
        spawnTankyEnemies();
        break;
      case 2:
        spawnNormalEnemies();
        break;
      case 3:
        spawnNormalEnemies();
        spawnNormalEnemies();
        break;
      case 4:
        spawnFastEnemies();
        spawnFastEnemies();
        break;
      case 5:
        spawnTankyEnemies();
        spawnTankyEnemies();
        break;
      case 6:
        spawnNormalEnemies();
        spawnTankyEnemies();
        break;
      case 7:
        spawnFastEnemies();
        spawnTankyEnemies();
        break;
      case 8:
        spawnNormalEnemies();
        spawnFastEnemies();
        break;
    }

    // Reset the clock after spawning enemies
    enemySpawnClock.restart();
  }

  // Update item spawning independently
  if (itemSpawnClock.getElapsedTime() >= spawnInterval) {
    int randomItem = rand() % 100;  // choose heals (>75) or weapon (<=75)

    if (randomItem < 75) {
      generateWeapons();
      std::cout << "Generating weapons..." << std::endl;  // Debug message
    } else {                                              // 25% chance
      generateHeals();
      std::cout << "Generating heals..." << std::endl;  // Debug message
    }
    // Reset the clock after spawning items
    itemSpawnClock.restart();
  }
}

// This function handles the display of the room, the entities within and
// also controls object interaction like pickups and collision logic
void Room::Display(sf::RenderWindow& window, Collider playerCollider,
                   Player& player, float deltaTime) {
  // Loops through each wall of the set room
  for (int x = 0; x < maxSize.x; x++) {
    for (int y = 0; y < maxSize.y; y++) {
      // Draws the concurrent wall obejct stored in layout
      layout[x][y].Draw(window);

      // Checks if current wall has collider
      if (layout[x][y].getColliderState() == true) {
        Collider wallCollider = layout[x][y].GetCollider();

        // Activate collision logic to ensure player collides with wall
        playerCollider.checkCollision(wallCollider, 0.0f);
      }
    }

    // Draw the weapons in the room
    for (Weapon* weapon : weapons) {
      weapon->Draw(window);
    }

    // Draw the healthpacks in the room
    for (Heals* healthPack : healthPacks) {
      healthPack->Draw(window);
    }

    // Draw the enemies in the room
    for (Enemy* enemy : enemies) {
      enemy->update(deltaTime, player);
      enemy->draw(window);
    }
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
    for (auto it = healthPacks.begin(); it != healthPacks.end();) {
      Heals* healthPack = *it;

      if (player.GetPosition().x < healthPack->getPosition().x + 50 &&
          player.GetPosition().x > healthPack->getPosition().x - 50 &&
          player.GetPosition().y < healthPack->getPosition().y + 50 &&
          player.GetPosition().y > healthPack->getPosition().y - 50) {
        if (player.equipHeal(healthPack)) {
          it = healthPacks.erase(it);
        } else {
          break;
        }
      } else {
        ++it;
      }
    }
  }

  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::E)) {  // Key 'E' for weapon pickup
    for (auto it = weapons.begin(); it != weapons.end();) {
      Weapon* weapon = *it;

      // Check if the player is within a certain range of the weapon
      if (player.GetPosition().x < weapon->getPosition().x + 50 &&
          player.GetPosition().x > weapon->getPosition().x - 50 &&
          player.GetPosition().y < weapon->getPosition().y + 50 &&
          player.GetPosition().y > weapon->getPosition().y - 50) {
        // Equip the weapon
        player.equipWeapon(weapon);
        it = weapons.erase(
            it);  // Remove the weapon from the map after picking it up
        std::cout << "Weapon collected!" << std::endl;
      } else {
        ++it;  // Move to the next weapon if no action is performed
      }
    }
  }

  for (size_t i = 0; i < enemies.size();) {
    Collider enemyCollider = enemies[i]->GetCollider();

    // Check collision with the player
    if (enemyCollider.checkCollision(playerCollider, 0.4f)) {
      player.takeDamage(enemies[i]->getDamage());
    }

    Weapon* playerWeapon = player.getCurrentWeapon();
    if (playerWeapon != nullptr) {
      std::vector<Projectile>& projectiles = playerWeapon->getProjectiles();

      // Iterate through projectiles
      for (size_t j = 0; j < projectiles.size();) {
        Collider projectileCollider = projectiles[j].GetCollider();

        // Wall collision check
        bool collidedWithWall = false;
        for (int x = 0; x < maxSize.x; x++) {
          for (int y = 0; y < maxSize.y; y++) {
            if (layout[x][y].getColliderState() == true) {
              Collider wallCollider = layout[x][y].GetCollider();
              enemyCollider.checkCollision(wallCollider, 0.0f);
              if (projectileCollider.checkCollision(wallCollider, 0.0f)) {
                // Erase projectile if it hits a wall
                projectiles.erase(projectiles.begin() + j);
                collidedWithWall = true;
                break;  // Break inner loops once a collision is detected
              }
            }
          }
          if (collidedWithWall) break;
        }

        // If we erased the projectile, skip incrementing j
        if (collidedWithWall) continue;

        // Enemy collision check
        if (projectileCollider.checkCollision(enemyCollider, 0.2f)) {
          // Projectile hits enemy
          projectiles.erase(projectiles.begin() + j);  // Erase projectile
          enemies[i]->takeDamage(playerWeapon->getDamage());

          // If enemy dies, erase the enemy
          if (enemies[i]->getHealth() == 0) {
            enemies.erase(enemies.begin() + i);
            player.increaseScore();
            break;  // Exit this enemy loop after erasing
          }

          // If projectile was erased, skip incrementing j
          continue;
        }

        // Increment j only if no erasures occurred
        ++j;
      }
    }

    // Increment i only if no enemies were erased
    ++i;
  }
}

void Room::spawnFastEnemies() {
  static sf::Texture fastEnemyTexture;
  static bool fastEnemyTextureLoaded = false;
  if (!fastEnemyTextureLoaded) {
    if (!fastEnemyTexture.loadFromFile("FastEnemy.png")) {
      std::cerr << "Error loading FastEnemy texture!" << std::endl;
      return;  // Exit the function if the texture fails to load
    }
    fastEnemyTextureLoaded = true;
  }

  for (int i = 0; i < 1; i++) {
    float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
    float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
    std::cout << "Spawning fast enemy at: (" << x << ", " << y << ")"
              << std::endl;  // Debug output

    Enemy* newEnemy =
        new FastEnemy(&fastEnemyTexture, sf::Vector2u(3, 4), 0.2f);
    newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
    enemies.push_back(newEnemy);
  }
}

void Room::spawnTankyEnemies() {
  static sf::Texture tankyEnemyTexture;
  static bool tankyEnemyTextureLoaded = false;
  if (!tankyEnemyTextureLoaded) {
    if (!tankyEnemyTexture.loadFromFile("TankyEnemy.png")) {
      std::cerr << "Error loading TankyEnemy texture!" << std::endl;
      return;  // Exit the function if the texture fails to load
    }
    tankyEnemyTextureLoaded = true;
  }

  for (int i = 0; i < 1; i++) {
    float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
    float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
    std::cout << "Spawning tanky enemy at: (" << x << ", " << y << ")"
              << std::endl;  // Debug output

    Enemy* newEnemy =
        new TankyEnemy(&tankyEnemyTexture, sf::Vector2u(3, 4), 0.2f);
    newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
    enemies.push_back(newEnemy);
  }
}

void Room::spawnNormalEnemies() {
  static sf::Texture normalEnemyTexture;
  static bool normalEnemyTextureLoaded = false;
  if (!normalEnemyTextureLoaded) {
    if (!normalEnemyTexture.loadFromFile("NormalEnemy.png")) {
      std::cerr << "Error loading Normal Enemy texture!" << std::endl;
      return;  // Exit the function if the texture fails to load
    }
    normalEnemyTextureLoaded = true;
  }

  for (int i = 0; i < 1; i++) {
    float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
    float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
    std::cout << "Spawning normal enemy at: (" << x << ", " << y << ")"
              << std::endl;  // Debug output

    Enemy* newEnemy =
        new NormalEnemy(&normalEnemyTexture, sf::Vector2u(6, 4), 0.2f);
    newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
    enemies.push_back(newEnemy);
  }
}

const float Room::VIEW_HEIGHT = 1200.0f;
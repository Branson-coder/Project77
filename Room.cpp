#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include <random>


using namespace std;

Room:: Room(sf::Texture* texture, sf::Vector2f position, int roomType){
	
    if (roomType == 1) {
        for (int x = 0; x < maxSize.x; x++) {
            layout.push_back(vector<Wall>());
            for (int y = 0; y < maxSize.y; y++) {
                
                if (x == 0 || x == maxSize.x - 1 || y == 0 || y == maxSize.y - 1 || y == 0){
                   
                    layout[x].push_back(Wall(texture, sf::Vector2f(100.0f, 100.f), position + sf::Vector2f(100.0f * x, 100.0f * y), sf::Color::White, true));


                } else {
                
                    layout[x].push_back(Wall(nullptr, sf::Vector2f(100.0f, 100.f), position + sf::Vector2f(100.0f * x, 100.0f * y), sf::Color::Transparent, false));
					
                }

				
            }
        }
        generateWeapons();
        spawnFastEnemies();
        spawnTankyEnemies();
        spawnNormalEnemies();
        generateHeals();
    }
}

void Room::generateWeapons(){
    static sf::Texture akTexture;
    static bool akTextureLoaded = false;
    if (!akTextureLoaded) {
        if (!akTexture.loadFromFile("AK47.png")) {
            std::cerr << "Error loading AK47 texture!" << std::endl; // debugging stuff just in case 
            return; 
        }
        akTextureLoaded = true;
    }

    static sf::Texture shotTexture;
    static bool shotTextureLoaded = false;
    if (!shotTextureLoaded) {
        if (!shotTexture.loadFromFile("SawedOff.png")) {
            std::cerr << "Error loading Sawed Off texture!" << std::endl; // debugging stuff just in case 
            return; 
        }
        shotTextureLoaded = true;
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
        
        for (int i = 0; i < 2; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")" << std::endl; 

        Weapon* newWeapon = new AK47(&akTexture, sf::Vector2f(50.0f, 50.0f), &projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);

    }

    for (int i = 0; i < 2; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning weapon at: (" << x << ", " << y << ")" << std::endl; 

        Weapon* newWeapon = new SawedOff(&shotTexture, sf::Vector2f(50.0f, 50.0f), &projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);

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

    for (int i = 0; i < 6; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1);
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
        std::cout << "Spawning health pack at: (" << x << ", " << y << ")" << std::endl;

        // Dynamically allocate the health pack
        Heals* newHealthPack = new Heals(sf::Vector2f(100.0f * x, 100.0f * y), &healTexture);
        healthPacks.push_back(newHealthPack);
    }
}

Room::~Room() {}

void Room::Display(sf::RenderWindow & window, Collider playerCollider, Player &player, float deltaTime){
	
	
	for (int x = 0; x < maxSize.x; x++)
	{
		for (int y = 0; y < maxSize.y; y++)
		{
			layout[x][y].Draw(window);
			if (layout[x][y].getColliderState() == true)
			{	
				Collider wallCollider = layout[x][y].GetCollider();
				playerCollider.checkCollision(wallCollider, 0.0f);
				
			}
		for (auto it = weapons.begin(); it != weapons.end(); ) { //using iterator cus its better
         Weapon* weapon = *it;  

        if (player.GetCollider().checkCollision(weapon->GetCollider(), 0.0f)) {
            player.equipWeapon(weapon); 
            it = weapons.erase(it);     // Remove the weapon and update the iterator
        } else {
            it++; 
        }
    }  
		}

        for (Weapon* weapon : weapons) {
        weapon->Draw(window);
        }
        
        for (Heals* healthPack : healthPacks) {
        healthPack->Draw(window);
        }
        for (Enemy* enemy : enemies) {
        enemy->update(deltaTime, player);
        enemy->draw(window); // Draw the enemy
       
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
}    
	
}


void Room::spawnFastEnemies(){
    static sf::Texture fastEnemyTexture;
    static bool fastEnemyTextureLoaded = false;
     if (!fastEnemyTextureLoaded) {
        if(!fastEnemyTexture.loadFromFile("FastEnemy.png")){
        std::cerr << "Error loading FastEnemy texture!" << std::endl;
        return; // Exit the function if the texture fails to load
        }
        fastEnemyTextureLoaded = true;
    }

        for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
         std::cout << "Spawning fast enemy at: (" << x << ", " << y << ")" << std::endl; // Debug output

        Enemy* newEnemy = new FastEnemy(&fastEnemyTexture, sf::Vector2u(3, 4), 0.2f);
        newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        enemies.push_back(newEnemy);

    }


}

void Room::spawnTankyEnemies(){
    static sf::Texture tankyEnemyTexture;
    static bool tankyEnemyTextureLoaded = false;
     if (!tankyEnemyTextureLoaded) {
        if(!tankyEnemyTexture.loadFromFile("TankyEnemy.png")){
        std::cerr << "Error loading TankyEnemy texture!" << std::endl;
        return; // Exit the function if the texture fails to load
        }
        tankyEnemyTextureLoaded = true;
    }

        for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
         std::cout << "Spawning tanky enemy at: (" << x << ", " << y << ")" << std::endl; // Debug output

        Enemy* newEnemy = new TankyEnemy(&tankyEnemyTexture, sf::Vector2u(3, 4), 0.2f);
        newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        enemies.push_back(newEnemy);

    }


}

void Room::spawnNormalEnemies() 
{
    static sf::Texture normalEnemyTexture;
    static bool normalEnemyTextureLoaded = false;
     if (!normalEnemyTextureLoaded) {
        if(!normalEnemyTexture.loadFromFile("NormalEnemy.png")){
        std::cerr << "Error loading Normal Enemy texture!" << std::endl;
        return; // Exit the function if the texture fails to load
        }
        normalEnemyTextureLoaded = true;
    }

        for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);
         std::cout << "Spawning normal enemy at: (" << x << ", " << y << ")" << std::endl; // Debug output

        Enemy* newEnemy = new NormalEnemy(&normalEnemyTexture, sf::Vector2u(6, 4), 0.2f);
        newEnemy->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        enemies.push_back(newEnemy);

    }

}
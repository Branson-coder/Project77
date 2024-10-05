#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include "Wall.h"
#include "AK47.h"

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
    
    static sf::Texture projectileTex;
    static bool projectileTexLoaded = false;
    if (!projectileTexLoaded) {
        if (!projectileTex.loadFromFile("Projectile.png")) {
            std::cerr << "Error loading projectile texture!" << std::endl;
            return; 
        }
        projectileTexLoaded = true;
    }
        
         for (int i = 0; i < 3; i++) {
        float x = static_cast<float>(rand() % static_cast<int>(maxSize.x - 2) + 1); 
        float y = static_cast<float>(rand() % static_cast<int>(maxSize.y - 2) + 1);

        Weapon* newWeapon = new AK47(&akTexture, sf::Vector2f(50.0f, 50.0f), &projectileTex);
        newWeapon->setPosition(sf::Vector2f(100.0f * x, 100.0f * y));
        weapons.push_back(newWeapon);

    }


}

void Room::Display(sf::RenderWindow & window, Collider playerCollider, Player &player){
	
	
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
			// need to implement the collision between weapon and player 
		}

        for (Weapon* weapon : weapons) {
        weapon->Draw(window); 
	}
	
}
}


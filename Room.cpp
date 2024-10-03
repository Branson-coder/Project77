#include <vector>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include "Wall.h"

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
			
		}
	}
	
}


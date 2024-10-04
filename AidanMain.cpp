#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "Room.h"
// g++ AidanMain.cpp Animation.cpp Wall.cpp Collider.cpp Player.cpp Room.cpp Projectile.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system
static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML game",
                            sf::Style::Close | sf::Style::Resize);

    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("Player.png");

    sf::Texture projectileTexture;
    projectileTexture.loadFromFile("Projectile.png");

    Player player(&playerTexture, sf::Vector2u(4, 4), 0.2f, 200.0f);

    sf::Vector2f screenSize(512.0f, 512.0f);

    sf::Texture wallTexture;
    wallTexture.loadFromFile("wall_texture.jpeg");

    sf::Vector2f roomPos(0.0f, 0.0f);
    Room room(&wallTexture, roomPos, 1);

    float deltaTime = 0.0f;
    sf::Clock clock;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized:
                    ResizeView(window, view);
                    break;
            }
        }

        player.Update(deltaTime);

        Collider playerCollider = player.GetCollider();

        
        view.setCenter(player.GetPosition());

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        room.Display(window, playerCollider, player);
        player.Draw(window);
        window.display();
    }

    return 0;
}
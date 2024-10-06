#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Wall.h"
#include "Room.h"

// g++ main.cpp Animation.cpp Wall.cpp Collider.cpp Player.cpp Room.cpp Projectile.cpp Weapon.cpp AssaultRifle.cpp AK47.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system

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
            if (evnt.type == sf::Event::Closed) window.close();
            if (evnt.type == sf::Event::Resized) ResizeView(window, view);
            if (evnt.type == sf::Event::KeyPressed) {
            if (evnt.key.code == sf::Keyboard::Space) {player.shoot(); }
        }
        }
        player.Update(deltaTime, window);

        Collider playerCollider = player.GetCollider();

        
        view.setCenter(player.GetPosition());

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);
        room.Display(window, playerCollider, player, deltaTime);
        player.Draw(window);


        
        window.display();
    }

    return 0;
}


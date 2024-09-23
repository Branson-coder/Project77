#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Wall.h"
// g++ BigManmain.cpp Collider.cpp Wall.cpp Animation.cpp Player.cpp -lsfml-graphics -lsfml-window -lsfml-system

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

    Player player(&playerTexture, sf::Vector2u(4, 4), 0.2f, 100.0f);

    sf::Vector2f screenSize(512.0f, 512.0f);

    sf::Texture wallTexture;
    wallTexture.loadFromFile("wall_texture.jpeg");

    Wall wall(&wallTexture, sf::Vector2f(100.0f, 100.0f), sf::Vector2f(500.0f, 200.0f));

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

        if(wall.GetCollider().checkCollision(player.GetCollider(), 1.0f)){
            std::cout<<"yay"<<std::endl;
        };
        view.setCenter(player.GetPosition());

        window.clear(sf::Color(0, 0, 0));
        window.setView(view);
        wall.Draw(window);
        player.Draw(window);
        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Wall.h"
#include "Room.h"
#include "HUD.h"
#include "Menu.h"

static const float VIEW_HEIGHT = 1080.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    int screenWidth = desktop.width;
    int screenHeight = desktop.height;

    // Create the main menu window
    sf::RenderWindow menuWindow(sf::VideoMode(512, 512), "Main Menu");
    menuWindow.setPosition(sf::Vector2i((screenWidth - 540) / 2, (screenHeight - 600) / 2)); // Center position
    Menu menu(menuWindow.getSize().x, menuWindow.getSize().y); // Initialize the menu

    // Declare variables needed for the game
    sf::RenderWindow gameWindow; // Game window
    sf::Texture playerTexture; // Player texture
    sf::Texture wallTexture; // Wall texture
    Player player(nullptr, sf::Vector2u(4, 4), 0.2f, 200.0f); // Player object
    Room room(nullptr, sf::Vector2f(0.0f, 0.0f), 1); // Room object
    sf::View view; // View for the game
    float deltaTime = 0.0f; // Time delta
    sf::Clock clock; // Clock to track time

    // Main menu loop
    while (menuWindow.isOpen()) {
        sf::Event event;
        while (menuWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                menuWindow.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    menu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Down) {
                    menu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    switch (menu.getSelectedItemIndex()) {
                        case 0: // Start Game
                            std::cout << "Start Game!\n";
                            //close menu window
                            menuWindow.close();

                            // Create the game window
                            gameWindow.create(sf::VideoMode(512, 512), "Pixel Gun 2D", sf::Style::Close | sf::Style::Resize);
                            gameWindow.setPosition(sf::Vector2i((screenWidth - 800) / 2, (screenHeight - 600) / 2)); // Center position
                            view.setSize(VIEW_HEIGHT, VIEW_HEIGHT); // Initialize view size
                            view.setCenter(0.0f, 0.0f); // Center the view

                            // Load textures
                            if (!playerTexture.loadFromFile("Player.png")) {
                                std::cerr << "Error loading Player.png" << std::endl;
                                return -1;
                            }
                            player = Player(&playerTexture, sf::Vector2u(4, 4), 0.2f, 200.0f);

                            if (!wallTexture.loadFromFile("wall_texture.jpeg")) {
                                std::cerr << "Error loading wall_texture.jpeg" << std::endl;
                                return -1;
                            }
                            room = Room(&wallTexture, sf::Vector2f(0.0f, 0.0f), 1);

                            // Load font and create HUD
                            {
                                sf::Font font;
                                if (!font.loadFromFile("font.otf")) { // Replace with your font file path
                                    std::cerr << "Error loading font.otf" << std::endl;
                                    return -1;
                                }
                                HUD hud(font, sf::Vector2f(1470.0f, 1000.0f), player); // Initialize HUD

                                // Game loop
                                while (gameWindow.isOpen()) {
                                    deltaTime = clock.restart().asSeconds();

                                    sf::Event evnt;
                                    while (gameWindow.pollEvent(evnt)) {
                                        if (evnt.type == sf::Event::Closed) gameWindow.close();
                                        if (evnt.type == sf::Event::Resized) ResizeView(gameWindow, view);
                                        if (evnt.type == sf::Event::KeyPressed) {
                                            if (evnt.key.code == sf::Keyboard::Space) {
                                                player.shoot();
                                            }
                                        }
                                    }

                                    player.Update(deltaTime, gameWindow);
                                    Collider playerCollider = player.GetCollider();
                                    view.setCenter(gameWindow.getSize().x / 2.75f, gameWindow.getSize().y / 2.2f); // Center the view
                                    //view.setCenter(player.GetPosition());

                                    gameWindow.clear(sf::Color(150, 150, 150));
                                    gameWindow.setView(view);
                                    room.Display(gameWindow, playerCollider, player, deltaTime);
                                    player.Draw(gameWindow);

                                    // Update and draw the HUD
                                    hud.update();
                                    hud.draw(gameWindow);
                                    gameWindow.display();
                                }
                            }
                            break;
                        case 1:
                            std::cout << "Show Tutorial!\n"; // Replace with tutorial display logic
                            break;
                        case 2:
                            menuWindow.close(); // Exit the game
                            break;
                    }
                }
            }
        }

        menuWindow.clear(sf::Color::Black);
        menu.draw(menuWindow);
        menuWindow.display();
    }

    return 0;
}

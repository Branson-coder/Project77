#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <SFML/System.hpp> 


#include "HUD.h"
#include "Menu.h"
#include "Player.h"
#include "Room.h"
#include "Wall.h"

using namespace std;

static const float VIEW_HEIGHT = 1080.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view) {
  float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
  view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int screenWidth = desktop.width;
  int screenHeight = desktop.height;

  // Declare variables needed for the game
  sf::RenderWindow gameWindow;  // Game window
  sf::RenderWindow tutWindow;   // tutorial window
  sf::Sprite tutSprite;         // sprite for tutorial png
  sf::Texture playerTexture;    // Player texture
  sf::Texture wallTexture;      // Wall texture
  sf::Texture tutTexture;       // texture for the tutorial

  Player player(nullptr, sf::Vector2u(4, 4), 0.2f, 200.0f);  // Player object
  Room room(nullptr, sf::Vector2f(0.0f, 0.0f), 1);           // Room object
  sf::View view;           // View for the game
  float deltaTime = 0.0f;  // Time delta
  sf::Clock clock;         // Clock to track time

  // main loop
  bool running = true;
  while (running) {
    // Create the main menu window
    sf::RenderWindow menuWindow(sf::VideoMode(1920, 1080), "Main Menu");
    menuWindow.setPosition(sf::Vector2i(
        (screenWidth - 1920) / 2, (screenHeight - 1080) / 2));  // Center position
    Menu menu(menuWindow.getSize().x,
              menuWindow.getSize().y);  // Initialize the menu
    // Main menu loop
    while (menuWindow.isOpen()) {
      sf::Event event;
      while (menuWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          menuWindow.close();
          running = false;
        }
        if (event.type == sf::Event::KeyPressed) {
          if (event.key.code == sf::Keyboard::Up) {
            menu.moveUp();
          }
          if (event.key.code == sf::Keyboard::Down) {
            menu.moveDown();
          }
          if (event.key.code == sf::Keyboard::Enter) {
            switch (menu.getSelectedItemIndex()) {
              case 0:  // Start Game
                std::cout << "Start Game!\n";
                // close menu window
                menuWindow.close();

                // Create the game window
                gameWindow.create(sf::VideoMode(1920, 1070), "Pixel Gun 2D",
                                  sf::Style::Close | sf::Style::Resize);
                gameWindow.setPosition(
                    sf::Vector2i((screenWidth - 1920) / 2,
                                 (screenHeight - 1070) / 2));  // Center position
                view.setSize(VIEW_HEIGHT, VIEW_HEIGHT);  // Initialize view size
                view.setCenter(0.0f, 0.0f);              // Center the view

                // Load textures
                if (!playerTexture.loadFromFile("Player.png")) {
                  std::cerr << "Error loading Player.png" << std::endl;
                  return -1;
                }
                player =
                    Player(&playerTexture, sf::Vector2u(4, 4), 0.2f, 200.0f);

                if (!wallTexture.loadFromFile("Wall.png")) {
                  std::cerr << "Error loading wall texture" << std::endl;
                  return -1;
                }
                room = Room(&wallTexture, sf::Vector2f(0.0f, 0.0f), 1);

                // Load font and create HUD
                {
                  sf::Font font;
                  if (!font.loadFromFile(
                          "font.otf")) {  // Replace with your font file path
                    std::cerr << "Error loading font.otf" << std::endl;
                    return -1;
                  }
                  HUD hud(font, sf::Vector2f(1470.0f, 1000.0f),
                          player);  // Initialize HUD

                  // Game loop
                  while (gameWindow.isOpen()) {
                    deltaTime = clock.restart().asSeconds();

                    sf::Event evnt;
                    while (gameWindow.pollEvent(evnt)) {
                      if (evnt.type == sf::Event::Closed) gameWindow.close();
                      if (evnt.type == sf::Event::Resized)
                        ResizeView(gameWindow, view);
                      if (evnt.type == sf::Event::KeyPressed) {
                        if (evnt.key.code == sf::Keyboard::Escape) {
                          gameWindow.close();  // Close the game window when Esc
                                               // is pressed
                          std::cout << "Returning to main menu...\n";
                        }
                      }
                      if (evnt.type == sf::Event::KeyPressed) {
                        if (evnt.key.code == sf::Keyboard::Space) {
                          player.shoot();
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                          player.useHeal();  // Player uses a heal
                        }
                      }
                    }

                    player.Update(deltaTime, gameWindow);
                    Collider playerCollider = player.GetCollider();
                    view.setCenter(
                        gameWindow.getSize().x / 2.75f,
                        gameWindow.getSize().y / 2.2f);  // Center the view

                    gameWindow.clear(sf::Color::Black);
                    gameWindow.setView(view);
                    room.update();
                    room.Display(gameWindow, playerCollider, player, deltaTime);
                    player.Draw(gameWindow);

                    // Update and draw the HUD
                    hud.update();
                    hud.draw(gameWindow);
                    gameWindow.display();

                    if (player.getHealth() <= 0) {
                      // Create Game Over Screen
                      sf::sleep(sf::milliseconds(500));
                      sf::RenderWindow gameOverWindow(sf::VideoMode(512, 512),
                                                      "Game Over");
                                                      gameOverWindow.setPosition(
                    sf::Vector2i((screenWidth - 512) / 2,
                                 (screenHeight - 512) / 2));  // Center position
        
                      sf::Font font;
                      if (!font.loadFromFile("font.otf")) {
                        std::cerr << "Error loading font.otf" << std::endl;
                        return -1;
                      }
                      sf::Text gameOverText;
                      gameOverText.setFont(font);
                      gameOverText.setString(
                          "GAME OVER!\nYour score "
                          "was: " +
                          std::to_string(player.getScore()) +
                          "\nPress Esc key to exit.");
                      gameOverText.setCharacterSize(50);
                      gameOverText.setFillColor(sf::Color::Red);
                      gameOverText.setPosition(50, 200);  // adjust as needed

                      while (gameOverWindow.isOpen()) {
                        sf::Event event;
                        while (gameOverWindow.pollEvent(event)) {
                          if (event.type == sf::Event::Closed) {
                            gameOverWindow.close();
                            running = false;
                          }
                          if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Escape) {
                              gameOverWindow.close();  // Exit the game
                              gameWindow.close(); //exit game
                            }
                          }
                        }

                        gameOverWindow.clear(sf::Color::Black);
                        gameOverWindow.draw(gameOverText);
                        gameOverWindow.display();
                      }
                      
                    }
                  }
                }
                break;
              case 1:
                std::cout
                    << "Show Tutorial!\n";  // Replace with tutorial display
                menuWindow.close();
                tutWindow.create(sf::VideoMode(1920, 1080), "Tutorial",
                                 sf::Style::Close | sf::Style::Resize);
                tutWindow.setPosition(
                    sf::Vector2i((screenWidth - 1920) / 2,
                                 (screenHeight - 1080) / 2));  // centre position
                view.setSize(VIEW_HEIGHT, VIEW_HEIGHT);       // set view size
                view.setCenter(0.0f, 0.0f);

                if (!tutTexture.loadFromFile("Tutorial.png")) {
                  std::cerr << "Error loading Tutorial.png" << std::endl;
                  return -1;
                }
                // sprite for the tutorial texture
                tutSprite.setTexture(tutTexture);
                tutSprite.setPosition(0.0f, 0.0f);

                while (tutWindow.isOpen()) {
                  deltaTime = clock.restart().asSeconds();
                  sf::Event evnt;
                  while (tutWindow.pollEvent(evnt)) {
                    if (evnt.type == sf::Event::Closed) tutWindow.close();
                    if (evnt.type == sf::Event::Resized)
                      ResizeView(tutWindow, view);
                    if (evnt.key.code == sf::Keyboard::Escape) {
                      tutWindow.close();  // Close the tutorial window when Esc
                                          // is pressed
                      std::cout << "Returning to main menu...\n";
                    }
                  }
                  tutWindow.clear();
                  tutWindow.draw(tutSprite);  // draw the tutorial sprite
                  tutWindow.display();
                }
                break;

              case 2:
                menuWindow.close();  // close the main menu
                running = false;     // end the program
                std::cout << "Exiting program" << std::endl;
                break;
            }
          }
        }
      }

      menuWindow.clear(sf::Color::Black);
      menu.draw(menuWindow);
      menuWindow.display();
    }
  }

  return 0;
}

// the main cpp file that runs the game
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

#include "GameOverMenu.h"
#include "HUD.h"
#include "Menu.h"
#include "Player.h"
#include "Room.h"
#include "Wall.h"

using namespace std;

int main() {
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int screenWidth = desktop.width;
  int screenHeight = desktop.height;

  // variables needed for the game
  sf::RenderWindow gameWindow;
  sf::RenderWindow tutWindow;
  sf::Texture playerTexture;
  sf::Texture wallTexture;
  sf::Texture tutTexture;

  Player player(nullptr, sf::Vector2u(4, 4), 0.2f, 200.0f);  // player object
  Room room(nullptr, sf::Vector2f(0.0f, 0.0f));              // room object
  sf::View view;           // view for the game
  float deltaTime = 0.0f;  // virtual time used for loop
  sf::Clock clock;         // clock to track time

  // loop that runs the program
  bool running = true;
  while (running) {
    // the main menu window
    sf::RenderWindow menuWindow(sf::VideoMode(1920, 1080), "Main Menu");
    menuWindow.setPosition(
        sf::Vector2i((screenWidth - 1920) / 2,
                     (screenHeight - 1080) / 2));  // centre position
    Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
    // main menu loop
    while (menuWindow.isOpen()) {
      sf::Event event;
      while (menuWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          menuWindow.close();
          running = false;  // if close button is pressed, exit the program
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
              case 0:                          // start the game
                std::cout << "Start Game!\n";  // debug message in terminal to
                                               // show game starting
                // close menu window
                menuWindow.close();

                // the game window
                gameWindow.create(sf::VideoMode(1920, 1080), "Pixel Gun 2D",
                                  sf::Style::Close | sf::Style::Resize);
                gameWindow.setPosition(sf::Vector2i(
                    (screenWidth - 1920) / 2,
                    (screenHeight - 1080) / 2));  // centre position
                view.setSize(Room::VIEW_HEIGHT,
                             Room::VIEW_HEIGHT);  // view size
                view.setCenter(0.0f, 0.0f);       // centre view

                // load textures
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
                room = Room(&wallTexture, sf::Vector2f(0.0f, 0.0f));

                // font and HUD
                {
                  sf::Font font;
                  if (!font.loadFromFile("font.otf")) {
                    std::cerr << "Error loading font.otf" << std::endl;
                    return -1;
                  }
                  HUD hud(font, sf::Vector2f(1920.0f, 1080.0f),
                          player);  // HUD

                  // game loop
                  while (gameWindow.isOpen()) {
                    deltaTime =
                        clock.restart()
                            .asSeconds();  // virtual time for game reset

                    sf::Event evnt;  // different variable name to event but
                                     // same thing essentially
                    while (gameWindow.pollEvent(evnt)) {
                      if (evnt.type == sf::Event::Closed) gameWindow.close();
                      if (evnt.type == sf::Event::Resized)
                        room.ResizeView(gameWindow, view);
                      if (evnt.type == sf::Event::KeyPressed) {
                        if (evnt.key.code == sf::Keyboard::Escape) {
                          gameWindow.close();  // close the game window when Esc
                                               // key is pressed
                          std::cout << "Returning to main menu...\n";
                        }
                      }
                      if (evnt.type == sf::Event::KeyPressed) {
                        if (evnt.key.code == sf::Keyboard::Space) {
                          player.shoot();  // if space is pressed, player shoots
                                           // projectile
                        }

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                          player.useHeal();  // player uses a heal
                        }
                      }
                    }

                    player.Update(
                        deltaTime,
                        gameWindow);  // update the player during the game
                    Collider playerCollider =
                        player.GetCollider();  // collider for the player
                    view.setCenter(
                        gameWindow.getSize().x / 2.75f,
                        gameWindow.getSize().y / 2.2f);  // centre the view

                    gameWindow.clear(sf::Color::Black);  // background for game
                                                         // window is black
                    gameWindow.setView(view);
                    room.update();  // update the room status
                    room.Display(gameWindow, playerCollider, player,
                                 deltaTime);  // display room elements
                    player.Draw(gameWindow);  // draw player model in game

                    // update and draw the HUD
                    hud.update();
                    hud.draw(gameWindow);
                    // display the game
                    gameWindow.display();

                    // when player loses and health reaches 0
                    if (player.getHealth() <= 0) {
                      // game over screen
                      sf::sleep(sf::milliseconds(
                          500));  // create real time delay to show user that
                                  // game is about to end

                      sf::RenderWindow gameOverWindow(sf::VideoMode(512, 512),
                                                      "Game Over");
                      GameOverMenu GameOverMenu(
                          font, std::to_string(
                                    player.getScore()));  // call constructor
                                                          // for game over menu

                      gameOverWindow.setPosition(sf::Vector2i(
                          (screenWidth - 512) / 2,
                          (screenHeight - 512) / 2));  // centre position

                      while (gameOverWindow.isOpen()) {
                        sf::Event event;
                        while (gameOverWindow.pollEvent(event)) {
                          if (event.type == sf::Event::Closed) {
                            gameOverWindow.close();
                            running = false;
                          }
                          if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Escape) {
                              gameOverWindow
                                  .close();        // exit the game over screen
                              gameWindow.close();  // exit game
                            }
                          }
                        }

                        gameOverWindow.clear(
                            sf::Color::Black);  // black background for game
                                                // over window
                        GameOverMenu.draw(
                            gameOverWindow);       // draw text for game over
                        gameOverWindow.display();  // display gameoverwindow
                      }
                    }
                  }
                }
                break;
              case 1:
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

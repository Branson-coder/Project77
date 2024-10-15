#include "GameState.h"

#include <fstream>

// Function to save the game state to a file
void GameState::saveGame(const GameState& game) {
  std::ofstream outFile("GameState.txt");

  if (outFile.is_open()) {
    outFile << game.getScore() << std::endl;
    outFile << game.getPlayerX() << std::endl;
    outFile << game.getPlayerY() << std::endl;
    outFile << game.getDeltaTime() << std::endl;
    outFile << game.getPlayerHealth() << std::endl;
    outFile.close();
    std::cout << "Game saved successfully!" << std::endl;
  } else {
    std::cerr << "Error: Unable to open file for saving!" << std::endl;
  }
}

// Function to load the game state from a file
void GameState::loadGame(GameState& game) {
  std::ifstream inFile("GameState.txt");

  if (inFile.is_open()) {
    int score;
    float playerX, playerY, deltaTime;

    inFile >> score;
    inFile >> playerX;
    inFile >> playerY;
    inFile >> deltaTime;

    game.setScore(score);
    game.setPlayerX(playerX);
    game.setPlayerY(playerY);
    game.setDeltaTime(deltaTime);
    game.setPlayerHealth(health);

    inFile.close();
    std::cout << "Game loaded successfully!" << std::endl;
  } else {
    std::cerr << "Error: Unable to open file for loading!" << std::endl;
  }
}

// default constructor
GameState::GameState() {
  this->score = 0;
  this->deltaTime = 0;
  this->playerX = 0;
  this->playerY = 0;
  isPaused = false;
}

void GameState::showPauseMenu(sf::RenderWindow& window) {
  sf::RenderWindow pauseWindow(sf::VideoMode(512, 512), "Paused");
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  int screenWidth = desktop.width;
  int screenHeight = desktop.height;
  pauseWindow.setPosition(
      sf::Vector2i((screenWidth - 512) / 2,
                   (screenHeight - 512) / 2));  // centre position

  // Font and text setup
  sf::Font font;
  if (!font.loadFromFile("font.otf")) {
    std::cerr << "Error loading font" << std::endl;
    return;
  }

  sf::Text pauseText("Game Paused", font, 30);
  pauseText.setPosition(100, 50);

  sf::Text resumeText("Press P to Resume", font, 20);
  resumeText.setPosition(50, 100);

  sf::Text quitText("Press Esc to Quit", font, 20);
  quitText.setPosition(50, 130);

  while (pauseWindow.isOpen()) {
    sf::Event event;
    while (pauseWindow.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        pauseWindow.close();
        window.close();  // Close main window
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::P) {
          pauseWindow.close();  // Resume the game
          togglePause();        // Toggle pause state
        }
        if (event.key.code == sf::Keyboard::Escape) {
          pauseWindow.close();
          window.close();  // Optional: exit the game
        }
      }
    }

    pauseWindow.clear(sf::Color::Black);
    pauseWindow.draw(pauseText);
    pauseWindow.draw(resumeText);
    pauseWindow.draw(quitText);
    pauseWindow.display();
  }
}

void GameState::togglePause() {
  isPaused = !isPaused;
  if (isPaused) {
    std::cout << "Game is now paused." << std::endl;
  } else {
    std::cout << "Game has resumed." << std::endl;
  }
}
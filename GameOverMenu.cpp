// this class is for the game over menu, with function to draw the text, and a
// constructor
#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(const sf::Font& font, const std::string& score) {
  gameOverText.setFont(font);
  gameOverText.setString("GAME OVER!");
  gameOverText.setCharacterSize(50);
  gameOverText.setFillColor(sf::Color::Red);
  gameOverText.setPosition(50, 100);

  scoreText.setFont(font);
  scoreText.setString("Your score was: " + score);
  scoreText.setCharacterSize(30);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(50, 200);

  instructionText.setFont(font);
  instructionText.setString("Press Esc key to exit.");
  instructionText.setCharacterSize(30);
  instructionText.setFillColor(sf::Color::White);
  instructionText.setPosition(50, 300);
}

void GameOverMenu::draw(sf::RenderWindow& window) {
  window.draw(gameOverText);
  window.draw(scoreText);
  window.draw(instructionText);
}

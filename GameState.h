#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Room.h"

class GameState {
 private:
  int score;
  float playerX, playerY;
  float deltaTime;
  int health;
  bool isPaused;

 public:
  GameState();  // default constructor

  int getScore() const { return score; }
  void setScore(int newScore) { score = newScore; }

  float getPlayerX() const { return playerX; }
  void setPlayerX(float x) { playerX = x; }

  float getPlayerY() const { return playerY; }
  void setPlayerY(float y) { playerY = y; }

  float getDeltaTime() const { return deltaTime; }
  void setDeltaTime(float dt) { deltaTime = dt; }

  int getPlayerHealth() const { return health; }
  void setPlayerHealth(int newHealth) { health = newHealth; }

  bool isGamePaused() const { return isPaused; }
  void togglePause();

  void showPauseMenu(sf::RenderWindow& window);  // to display pause menu
  // functions for saving and loading the game state
  void saveGame(const GameState& game);
  void loadGame(GameState& game);
};

#endif

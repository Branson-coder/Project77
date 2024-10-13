// this class contains the main menu for the game, where users will interact
// with the window
#include "Menu.h"

#include <iostream>

Menu::Menu(float width, float height) {
  if (!font.loadFromFile("font.otf")) {
    std::cerr << "Error loading font\n";
  }

  // title
  title.setFont(font);
  title.setString("Pixel Gun 2D");
  title.setCharacterSize(100);
  title.setFillColor(sf::Color::White);
  title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 4);

  // menu options
  startText.setFont(font);
  startText.setString("Start");
  startText.setCharacterSize(50);
  startText.setFillColor(sf::Color::White);
  startText.setPosition(width / 2 - startText.getGlobalBounds().width / 2,
                        height / 2);

  // exit
  exitText.setFont(font);
  exitText.setString("Exit");
  exitText.setCharacterSize(50);
  exitText.setFillColor(sf::Color::White);
  exitText.setPosition(width / 2 - exitText.getGlobalBounds().width / 2,
                       height / 2 + 60);

  selectedItemIndex = 0;
  updateSelection();
}

//draw text in window
void Menu::draw(sf::RenderWindow &window) {
  window.draw(title);
  window.draw(startText);
  window.draw(exitText);
}

//functions to move the selection
void Menu::moveUp() {
  if (selectedItemIndex - 1 >= 0) {
    selectedItemIndex--;
    updateSelection();
  }
}


void Menu::moveDown() {
  if (selectedItemIndex + 1 < 2) {
    selectedItemIndex++;
    updateSelection();
  }
}

//the selection is returned
int Menu::getSelectedItemIndex() const { return selectedItemIndex; }

//update the selection by indicating which is highlighted
void Menu::updateSelection() {
  startText.setFillColor(selectedItemIndex == 0 ? sf::Color::Red
                                                : sf::Color::White);
  exitText.setFillColor(selectedItemIndex == 1 ? sf::Color::Red
                                               : sf::Color::White);
}
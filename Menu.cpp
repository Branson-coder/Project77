#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height) {
    // Load font
    if (!font.loadFromFile("font.otf")) {
        std::cerr << "Error loading font\n";
    }

    // Title
    title.setFont(font);
    title.setString("Pixel Gun 2D");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(width / 2 - title.getGlobalBounds().width / 2, height / 4);

    // Menu options
    startText.setFont(font);
    startText.setString("Start");
    startText.setCharacterSize(30);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(width / 2 - startText.getGlobalBounds().width / 2, height / 2);

    tutorialText.setFont(font);
    tutorialText.setString("Tutorial");
    tutorialText.setCharacterSize(30);
    tutorialText.setFillColor(sf::Color::White);
    tutorialText.setPosition(width / 2 - tutorialText.getGlobalBounds().width / 2, height / 2 + 40);

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(width / 2 - exitText.getGlobalBounds().width / 2, height / 2 + 80);

    // Initialize selected option
    selectedItemIndex = 0;
    updateSelection();
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(title);
    window.draw(startText);
    window.draw(tutorialText);
    window.draw(exitText);
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        selectedItemIndex--;
        updateSelection();
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < 3) {
        selectedItemIndex++;
        updateSelection();
    }
}

int Menu::getSelectedItemIndex() const {
    return selectedItemIndex;
}

void Menu::updateSelection() {
    startText.setFillColor(selectedItemIndex == 0 ? sf::Color::Red : sf::Color::White);
    tutorialText.setFillColor(selectedItemIndex == 1 ? sf::Color::Red : sf::Color::White);
    exitText.setFillColor(selectedItemIndex == 2 ? sf::Color::Red : sf::Color::White);
}

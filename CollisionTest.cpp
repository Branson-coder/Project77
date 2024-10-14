#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Collider.h"

//g++ -o coll CollisionTest.cpp Collider.cpp -lsfml-graphics -lsfml-window -lsfml-system

// Function to test non-collision between two rectangles
void testCollider1() {
    // Create two rectangle shapes with different sizes
    sf::RectangleShape rect1(sf::Vector2f(100.0f, 100.0f));
    rect1.setPosition(200.0f, 200.0f);

    sf::RectangleShape rect2(sf::Vector2f(100.0f, 100.0f));
    rect2.setPosition(400.0f, 200.0f); 

    // Create Collider objects for each rectangle
    Collider collider1(rect1);
    Collider collider2(rect2);

    // Check collision between the two colliders
    bool collided = collider1.checkCollision(collider2, 0.5f);

    // Assert that the collision did not occurr since they do not overlap
    assert(collided == false); 
    std::cout << "Collision test1 passed!" << std::endl;
}


void testCollider2() {
    // Create two rectangle shapes with different sizes
    sf::RectangleShape rect1(sf::Vector2f(100.0f, 100.0f));
    rect1.setPosition(200.0f, 200.0f);

    sf::RectangleShape rect2(sf::Vector2f(100.0f, 100.0f));
    rect2.setPosition(250.0f, 200.0f); // Adjusted to create an overlap

    Collider collider1(rect1);
    Collider collider2(rect2);

    // Test collision between the two colliders
    bool collided = collider1.checkCollision(collider2, 0.5f);

    // Assert that the collision occurred
    assert(collided == true); // Expect collision since they are overlapping
    std::cout << "Collision test2 passed!" << std::endl;
}

int main() {
    testCollider1();
    testCollider2(); 
    std::cout << "All tests passed!" << std::endl;
    return 0;
}

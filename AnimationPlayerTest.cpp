// Unit test to test the movement and animation of the player
// a class is created to isolate the movement of the player using animation
// functionality Compile with g++ AnimationPlayerTest.cpp -lsfml-graphics
// -lsfml-window -lsfml-system -o AnimationPlayerTest
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class AnimationPlayerTest {
 public:
  // constructor
  AnimationPlayerTest(sf::Texture* texture, sf::Vector2u imageCount,
                      float switchTime, float speed)
      : speed(speed),
        row(0),
        totalTime(0.0f),
        currentImage(0, 0),
        switchTime(switchTime) {
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y / float(imageCount.y);
    body.setSize(sf::Vector2f(70.0f, 70.0f));
    body.setOrigin(body.getSize() / 2.0f);
    body.setPosition(206.0f, 206.0f);
    body.setTexture(texture);
  }

  // update the movement of user input such as wasd
  void Update(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);
    bool isMoving = false;

    // method to track key press states so that the terminal can display user
    // input
    static bool keysPressed[4] = {false, false, false,
                                  false};  // set to false initially

    // movement and facing direction
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {  // left
      movement.x -= speed * deltaTime;
      row = 2;                // player animation facing left
      if (!keysPressed[0]) {  // this if statement is added to stop terminal
                              // from repeating the output
        std::cout << "User pressed 'A' key, moving left" << std::endl;
        keysPressed[0] =
            true;  // set pressed key A to true so it does not repeat loop
      }
      isMoving = true;
    } else {
      keysPressed[0] = false;  // reset when the key is released
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {  // right
      movement.x += speed * deltaTime;
      row = 3;
      if (!keysPressed[1]) {
        std::cout << "User pressed 'D' key, moving right" << std::endl;
        keysPressed[1] = true;
      }
      isMoving = true;
    } else {
      keysPressed[1] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {  // up
      movement.y -= speed * deltaTime;
      row = 1;
      if (!keysPressed[2]) {
        std::cout << "User pressed 'W' key, moving up" << std::endl;
        keysPressed[2] = true;
      }
      isMoving = true;
    } else {
      keysPressed[2] = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {  // down
      movement.y += speed * deltaTime;
      row = 0;
      if (!keysPressed[3]) {
        std::cout << "User pressed 'S' key, moving down" << std::endl;
        keysPressed[3] = true;
      }
      isMoving = true;
    } else {
      keysPressed[3] = false;
    }

    // move the player and update animation
    if (isMoving) {
      totalTime += deltaTime;
      if (totalTime >= switchTime) {
        totalTime -= switchTime;
        currentImage.x++;
        if (currentImage.x >= 4) {
          currentImage.x = 0;
        }
      }
      uvRect.left = currentImage.x * uvRect.width;
      uvRect.top = row * uvRect.height;
      body.setTextureRect(uvRect);
      body.move(movement);
    } else {
      currentImage.x = 0;
      uvRect.left = currentImage.x * uvRect.width;
      body.setTextureRect(uvRect);
    }
  }

  // draw the player model in the window
  void Draw(sf::RenderWindow& window) { window.draw(body); }

 private:
  sf::RectangleShape body;  
  sf::IntRect uvRect;       
  float speed;
  int row;
  float totalTime;
  float switchTime;           
  sf::Vector2u currentImage;  
};

void testPlayerMovement() {
  sf::Texture playerTexture;
  if (!playerTexture.loadFromFile("Player.png")) {
    std::cerr << "Error loading Player.png" << std::endl;
    return;
  }

  AnimationPlayerTest player(&playerTexture, sf::Vector2u(4, 4), 0.2f,
                             200.0f);  

  sf::RenderWindow window(sf::VideoMode(512, 512), "Player Movement Test");
  sf::Clock clock; 

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

  
    float deltaTime = clock.restart().asSeconds();

 
    player.Update(deltaTime);

   
    window.clear();

   
    player.Draw(window);

  
    window.display();
  }
}

int main() {
  testPlayerMovement();
  return 0;
}

// this class controls the animation of the player and enemies, allowing a
// seamless movement experience for the user

#include "Animation.h"

#include <iostream>
using namespace std;

// constructor for animation class requires parameters such as a pointer to
// texture, the imagecount for the number of images considered when animating,
// and switchtime which controls when the image should change
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount,
                     float switchTime) {
  // initialise variables
  this->imageCount = imageCount;
  this->switchTime = switchTime;
  totalTime = 0.0f;
  currentImage.x = 0;

  // debugging check because of segmentation faults at the beginning of the game 
  if (texture == nullptr) {
    return;
  }
  // affects the animation such that it displays the correct image
  uvRect.width = texture->getSize().x / float(imageCount.x);
  uvRect.height = texture->getSize().y / float(imageCount.y);
}

Animation::~Animation() {}

void Animation::Update(int row, float deltaTime) {
  // animation works via deltatime and the row of the image. e.g. row 0 might
  // control the animation of player movement
  //  facing up whilst row 3 controls facing down
  currentImage.y = row;
  totalTime += deltaTime;

  // if statement to control whether image displays whilst the animation is
  // running
  if (totalTime >= switchTime) {
    totalTime -= switchTime;
    currentImage.x++;

    // if the current image in the row is higher or equal to the imagecount,
    // then it resets back,
    // essentially creating a loop
    if (currentImage.x >= imageCount.x) {
      currentImage.x = 0;
    }
  }
  // creates the image according to the size of the image and how many sprites
  // there are
  uvRect.left = currentImage.x * uvRect.width;
  uvRect.top = currentImage.y * uvRect.height;
}

// this function resets the current image when the player is not moving.
void Animation::ResetCurrentImage() { currentImage.x = 0; }

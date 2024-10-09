#include "Animation.h"
#include <iostream>
using namespace std;

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) 
{
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;

        // Check if the texture pointer is valid
    if (texture == nullptr) {
        std::cerr << "Error: Texture pointer is null!" << std::endl;
        // Optionally, you can set default values for uvRect
        uvRect.width = 0;
        uvRect.height = 0;
        return; // Early return to avoid dereferencing a null pointer
    }

    uvRect.width = texture->getSize().x / float (imageCount.x);
    uvRect.height = texture->getSize().y / float (imageCount.y);
}

Animation::~Animation() {}

void Animation::Update(int row, float deltaTime)
{
    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }

    }

    uvRect.left = currentImage.x * uvRect.width;
    uvRect.top = currentImage.y * uvRect.height;
    
}

void Animation::ResetCurrentImage() 
{
    currentImage.x = 0;
    
}

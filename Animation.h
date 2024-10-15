//header file for animation class
#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{

    private:
        //these variables are for the image that is displayed on the screen for the animation
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        //controls which image is displayed according to the 'virtual' time that has passed
        float totalTime;
        float switchTime;

    public:
        //constructor
        Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
        //destructor
        ~Animation();

        //update the animation
        void Update(int row, float deltaTime);

        //create a sfml integer rectangle for the image that is displayed
        sf::IntRect uvRect;

        //function to reset image displayed
        void ResetCurrentImage();


};

#endif
#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
#include "Player.h"
#include "Projectile.h"
using namespace std;

class Enemy
{
    protected:
        sf::RectangleShape body;
        Animation animation;
        Projectile enemyProjectile;
        
        sf::Vector2f direction;
        sf::Vector2f movement;

        unsigned int row;
        float speed;
        float currentSpeed;
        float pause = .2f;
        float health;
        float timeDelay;
        float damage;
        float chargeTime = 3;
        float steps = 0;
        int type;

        bool faceRight;
        bool faceUp;
        bool active;
           

    

    public:
        Enemy(sf::Texture* texture, sf::Vector2u imageCount, sf::Vector2f spawnPos, Projectile projectile, float switchTime, int type);
        ~Enemy();
        
        void update(float deltaTime, Player player);
        void updateProjectile(float deltaTime);
        void draw(sf::RenderWindow& window);
        void drawProjectile(sf::RenderWindow& window);
        void takeDamage(float damage);
        void setActive();

        sf::Vector2f getPosition()
        {
            return body.getPosition();

        }

        float getHealth()
        {

            return health;
        }


        Collider getCollider()
        {
            return Collider(body);

        }

        vector<Projectile> getProjectile()
        {
            return projectile;
        }

        float getDamage()
        {
            return damage;

        }

        void setPosition(sf::Vector2f startPosition)
        {
            body.setPosition(startPosition);
        }

        vector<Projectile> projectile;


};




#endif
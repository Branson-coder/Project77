#include "Weapon.h"
#include "Collider.h"
#include "Projectile.h"

Weapon::Weapon(sf::Texture* texture, sf::Vector2f size, float fireRate, float damage)
    : damage(damage), fireRate(fireRate), maxAmmo(30), currentAmmo(maxAmmo), collider(body)  // Example values
{
    body.setSize(size);
    body.setTexture(texture);
    body.setOrigin(size / 2.0f);
}

Weapon::~Weapon(){
    
}
sf::RectangleShape Weapon::getBody() const {
    return body;
}


void Weapon::setPosition(sf::Vector2f position) {
    body.setPosition(position);
}



void Weapon::updateProjectiles(float deltaTime, const sf::RenderWindow& window) {
    (void)window;
    for (size_t i = 0; i < projectiles.size(); ++i) {
        projectiles[i].Update(deltaTime);
    }
}

void Weapon:: Draw(sf::RenderWindow& window){
    window.draw(body);
}

void Weapon::drawProjectiles(sf::RenderWindow& window) {
   for (size_t i = 0; i < projectiles.size(); i++)
	{
		projectiles[i].Draw(window);
	}
}

int Weapon::getAmmo() {
    return currentAmmo;  // Return the current ammo count
}
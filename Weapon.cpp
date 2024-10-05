#include "Weapon.h"
#include "Collider.h"

Weapon::Weapon(sf::Texture* texture, sf::Vector2f size, float fireRate, float damage)
    : damage(damage), fireRate(fireRate), maxAmmo(30), currentAmmo(maxAmmo)  // Example values
{
    body.setSize(size);
    body.setTexture(texture);
    body.setOrigin(size / 2.0f);
}

sf::RectangleShape Weapon::getBody() const {
    return body;
}


void Weapon::setPosition(sf::Vector2f position) {
    body.setPosition(position);
}


// this needs more work
void Weapon::updateProjectiles(float deltaTime, const sf::RenderWindow& window) {
    for (size_t i = 0; i < projectiles.size(); ++i) {
        projectiles[i].Update(deltaTime);
        if (projectiles[i].isOffScreen(window) || projectiles[i].getLifetime() <= 0) {
            projectiles.erase(projectiles.begin() + i);
            --i;
        }
    }
}

void Weapon:: Draw(sf::RenderWindow& window){
    window.draw(body);
}

void Weapon::drawProjectiles(sf::RenderWindow& window) {
    for (auto& projectile : projectiles) {
        projectile.Draw(window);
    }
}

#include "wasp.h"
#include "game.h" // Include the game header to access game::BohaterPosition
#include "bohater.h"
#include "GameGlobals.h"
#include <cstdlib> // Include this for random number generation
#include <ctime>   // Include this for seeding the random number generator
float wasp::CalculateRotationAngle(const sf::Vector2f& source, const sf::Vector2f& target) {
    float dx = target.x - source.x;
    float dy = target.y - source.y;
    return std::atan2(dy, dx) * 180 / static_cast<float>(pi);
}

void wasp::updateBohaterPosition(sf::Vector2f newPosition) {
    bohaterPosition = newPosition;
    //wstd::cout << bohaterPosition.x << bohaterPosition.y;
}

void wasp::update(float time){
    if (isDead == false) {
        this->setRotation(CalculateRotationAngle(this->getPosition(), bohaterPosition) + 90);
    }
    MyGame::bohater* bohater = MyGame::gameInstance.bohaterInstance.get();
    if (hp<=0) {
        corpse.loadFromFile("textures/Corpse.png");
        speed = 0;
        isDead = true;
    }
    
}

void wasp::move(float time) {
    if (isDead == false) {
        // Implement your move logic here
        float angleRadians = (this->getRotation() - 90) * pi / 180.0f;

        // Calculate the movement vector based on the angle
        sf::Vector2f movement(std::cos(angleRadians), std::sin(angleRadians));

        // Scale the movement vector by the speed
        movement *= speed;

        // Update the position based on the movement vector and elapsed time
        this->setPosition(this->getPosition() + movement * time);
    }
}

wasp::wasp(float diff) {
    this->hp = this->hp * diff;
    this->speed = this->speed * diff*0.5;
    // Generate a random speed multiplier between 0.8 and 1.2
    float speedMultiplier = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));

    // Apply the multiplier to the basic speed
    speed *= speedMultiplier;
    teksturabazowa.loadFromFile("textures/wasp.png");
    this->setTexture(teksturabazowa);
    // Generate a random x-coordinate at the top of the screen
    float randomX = static_cast<float>(std::rand() % 1920); // Assuming a screen width of 1920 pixels

    // Set the initial position with the random x-coordinate and a fixed y-coordinate (at the top)
    this->setPosition(randomX, 100); // 0 is the top of the screen
    sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
    setOrigin(size.x / 2, size.y / 2);
}
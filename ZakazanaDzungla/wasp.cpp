#include "wasp.h"
#include "game.h" // Include the game header to access game::BohaterPosition
#include "bohater.h"
#include "GameGlobals.h"
#include <cstdlib> // Include this for random number generation
#include <ctime>   // Include this for seeding the random number generator

bool wasp::callIsDead()
{
    return isDead;
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
        this->setTexture(corpse);
        speed = 0;
        isDead = true;
        isActive = false;
    }
    
}

void wasp::takeDamage(int damage)
{
    hp -= damage;
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
    speed = speed * diff*0.5;
    // Generate a random speed multiplier between 0.8 and 1.2
    float speedMultiplier = 0.8f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.2f - 0.8f)));

    // Apply the multiplier to the basic speed
    speed *= speedMultiplier * diff;
    //if (!teksturabazowa.loadFromFile("textures/wasp.png")) {
    //    // Handle error loading texture
    //}
    //frames.push_back(teksturabazowa);
    //if (!teksturabazowa.loadFromFile("textures/wasp2.png")) {
    //    // Handle error loading texture
    //}
    //frames.push_back(teksturabazowa);
    //for (int i = 1; i <= 2; i++) {
    //    sf::Texture frame;
    //    
    //    
    //}
    teksturabazowa.loadFromFile("textures/wasp.png");
    this->setTexture(teksturabazowa);
    // Generate a random x-coordinate at the top of the screen
   // Assuming a screen width of 1920 pixels and a screen height of 1080 pixels
    int screenWidth = 1920;
    int screenHeight = 1080;

    // Randomly choose the spawn side (0: top, 1: right, 2: bottom, 3: left)
    int spawnSide = std::rand() % 4;

    float randomX, randomY;

    switch (spawnSide) {
    case 0: // Spawn on top
        randomX = static_cast<float>(std::rand() % screenWidth);
        randomY = -100.0f;
        break;
    case 1: // Spawn on the right
        randomX = screenWidth + 100.0f;
        randomY = static_cast<float>(std::rand() % screenHeight);
        break;
    case 2: // Spawn on the bottom
        randomX = static_cast<float>(std::rand() % screenWidth);
        randomY = screenHeight + 100.0f;
        break;
    case 3: // Spawn on the left
        randomX = -100.0f;
        randomY = static_cast<float>(std::rand() % screenHeight);
        break;
    default:
        // Handle unexpected case (this should never happen)
        break;
    }

    this->setPosition(randomX, randomY);
    sf::Vector2f size = static_cast<sf::Vector2f>(teksturabazowa.getSize());
    setOrigin(size.x / 2, size.y / 2);
}
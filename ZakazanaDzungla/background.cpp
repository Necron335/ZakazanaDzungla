#include "background.h"

background::background()
{
    backgroundTexture.loadFromFile("textures/trawa.png");
    this->setTexture(backgroundTexture);
    this->setPosition(0, 0);
}

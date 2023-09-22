#include "entities.h"




float entities::CalculateRotationAngle(const sf::Vector2f& source, const sf::Vector2f& target)
{
    float dx = target.x - source.x;
    float dy = target.y - source.y;
    return std::atan2(dy, dx) * 180 / static_cast<float>(pi);
}
void entities::calla(sf::Vector2f newPosition)
{

    updateBohaterPosition(newPosition);

}
void entities::updateBohaterPosition(sf::Vector2f newPosition)
{
    bohaterPosition = newPosition;
}

#pragma once
#include "entities.h"
class projectiles : public entities
{
protected:
	float speed = 100;
	sf::Vector2f direction;
	int damage = 0;
	sf::Clock alivetime;
	float timetodie = 10;
};


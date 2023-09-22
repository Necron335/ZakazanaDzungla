#include "enemies.h"

void enemies::takeDamage(int damage)
{
	this->hp -= damage;
}

void enemies::calltk(int damage)
{
	takeDamage(damage);
}

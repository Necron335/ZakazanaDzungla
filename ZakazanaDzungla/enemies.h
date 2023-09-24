#pragma once
#include "entities.h"
class enemies :   public entities
{
protected:
	float hp = 10;
	//Damage is redundant here but hey, it looks cool
	float damage = 1;
public:
	virtual void move() {

	}
	virtual void takeDamage(int damage) {};
	void calltk(int damage);
};


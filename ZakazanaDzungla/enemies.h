#pragma once
#include "entities.h"
class enemies :   public entities
{
protected:
	float hp = 10;
	float damage = 1;
public:
	virtual void move() {

	}
	void takeDamage(int damage);
	void calltk(int damage);
};


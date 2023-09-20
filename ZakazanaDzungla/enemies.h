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
};


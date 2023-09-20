#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
class entities: public sf::Sprite
{
protected:
	float speed = 0;
	float rotationAngle = 0;
	sf::Texture teksturabazowa;
	sf::Texture corpse;
public:
	virtual bool isWasp() const { return false; }
	virtual void update(float time) {

	}
	virtual void move(float time) {

	}


};


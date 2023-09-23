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
	float CalculateRotationAngle(const sf::Vector2f& source, const sf::Vector2f& target);
	float speed = 0;
	float rotationAngle = 0;
	sf::Texture teksturabazowa;
	sf::Texture corpse;
	bool isDead = false;
	bool isActive = true;
	float pi = 3.1415;
	sf::Vector2f bohaterPosition;
	int hp = 10;

	void updateBohaterPosition(sf::Vector2f newPosition);
public:
	virtual bool isWasp() const { return false; }
	virtual bool isBullet() const { return false; }
	virtual void update(float time) {

	}
	virtual void move(float time) {

	}
	virtual bool callIsDead() { return false; };
	virtual bool callIsActive() { return isActive; };
	virtual void takeDamage(int damage) {}
	virtual void handleCollisionWithEnemy() {}
	void calla(sf::Vector2f newPosition);

};


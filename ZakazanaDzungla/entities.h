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
	//basic data
	float CalculateRotationAngle(const sf::Vector2f& source, const sf::Vector2f& target);
	float speed = 0;
	float rotationAngle = 0;
	sf::Texture teksturabazowa;
	sf::Texture corpse;
	bool isDead = false;
	bool isActive = true;
	float pi = 3.1415;
	sf::Vector2f bohaterPosition;
	float hp = 10;
	std::vector<sf::Texture> frames;

	void updateBohaterPosition(sf::Vector2f newPosition);
public:
	//those are for game to check if entity is something specific, veeery useful for invector usage
	virtual bool isWasp() const { return false; }
	virtual bool isCharger() const { return false; }
	virtual bool isShooter() const { return false; }
	virtual bool isBullet() const { return false; }
	virtual bool isBolt() const { return false; }
	virtual bool isSwing() const { return false; }
	//virtual void for update and move, self explainatory i guess
	virtual void update(float time) {

	}
	virtual void move(float time) {

	}
	//works similarry to isSomething bools, just for returning isDead or Active state
	virtual bool callIsDead() { return false; };
	virtual bool callIsActive() { return isActive; };
	//Only enemies need this but this combined with bools makes everything easier
	virtual void takeDamage(int damage) {}
	//and this is for projectiles;)
	virtual void handleCollisionWithEnemy() {}
	//Its to recall bohaterpositiion, but I think i replaced it but i dont want to touch it in case i break this jenga tower
	void calla(sf::Vector2f newPosition);

};


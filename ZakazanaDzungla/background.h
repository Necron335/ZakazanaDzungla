#pragma once
#include<iostream>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class background : public sf::Sprite
{
public:
	sf::Sprite backgroundSprite;
	sf::Texture backgroundTexture;
	background();
};


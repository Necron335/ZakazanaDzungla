#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include"game.h"
#include <cstdlib>
#include <ctime>

namespace MyGame {
    game gameInstance; // Define gameInstance here
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    MyGame::gameInstance.run();
    return 0;
}

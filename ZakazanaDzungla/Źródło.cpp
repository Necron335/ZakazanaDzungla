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
    game gameInstance(1); // Wpisz poziom trudnosci
    // W aby poruszac sie do prodzu
    //myszka to cel pozycji gracza
    // Aby wybrac bron nalezy nacisnac 1 2 lub 3 dla roznych broni
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    MyGame::gameInstance.run();
    return 0;
}

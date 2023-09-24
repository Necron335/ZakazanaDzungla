#pragma once
#include "game.h"

namespace MyGame {
    extern game gameInstance; // Declare the global gameInstance variable
    //I wanted to use this to deliver pi to everywhere since i have calculations in radians
    //Also gameInstance for calling functions from game, for example i wanted to call function to spawnStinger but i cant get it to work:\
    constexpr double pi = 3.1415;
}
class GameGlobals
{
};


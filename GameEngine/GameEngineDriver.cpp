#include "GameEngine.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const string MAP_DIRECTORY = "../maps/";

int main() {
    srand(time(0));

    GameEngine* gameEngine = GameEngine::getInstance();
    gameEngine->startupPhase();
    gameEngine->mainGameLoop();

    delete gameEngine;

    return 0;
}
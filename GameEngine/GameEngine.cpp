#include <fstream>
#include "GameEngine.h"
#include "../MapLoader/MapLoader.h"
#include "../Player/Player.h"
#include <random>
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;

//GAME INITIALIZATION PHASE

void GameInitialization::selectMap() {
    const string MAP_DIRECTORY = "../maps/";
    int chosenMap;
    ifstream inputFile;
    do {
        cout << "Please choose a game Map from the following list:" << endl;
        std::string path = "../maps/";
        setAvailableMaps(path);
        for (int i = 1; i <= availableMaps.size(); i++) {
            cout << i << " - " << availableMaps.at(i - 1) << endl;
        }
        cin >> chosenMap;
        inputFile.open(MAP_DIRECTORY + availableMaps.at(chosenMap - 1));
        while (!inputFile) {
            inputFile.close();
            cout << "Hey you made a mistake, " << chosenMap << " is not one of the choices." << endl;
            cout << "Please pick another map now: " << endl;
            cin >> chosenMap;
            inputFile.open(MAP_DIRECTORY + availableMaps.at(chosenMap - 1));
        }
        this->map = MapLoader::loadMap(availableMaps.at(chosenMap - 1));
    } while (!map->validate());
    inputFile.close();
}

void GameInitialization::setAvailableMaps(const string &path) {
    for (const auto &entry : fs::directory_iterator(path))
        if (!entry.is_directory())
            this->availableMaps.push_back(entry.path().filename());
}

void GameInitialization::selectPlayerNumber() {
    int numPlayerTmp = -1;
    cout << "The game supports up to 5 players with a minimum of 2."
            " Please input the desired number of players" << endl;
    cin >> numPlayerTmp;
    while (numPlayerTmp < 2 or numPlayerTmp > 5) {
        cout << "This does not look like a number between 2 to 5."
                "The game supports up to 5 players with a minimum of 2."
                " Please input the desired number of players" << endl;
        cin >> numPlayerTmp;
        if (cin.fail()) {
            cin.clear();
            numPlayerTmp = 0;
            // discard 'bad' character(s)
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    this->numPlayer = numPlayerTmp;
}

void GameInitialization::setupObservers() {

    //  3) turn on/off any of the observers as described in Part 5
    do {
        cin.clear();
        phaseObserver = false;
        // discard 'bad' character(s)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ok almost done, do you want to turn on the phase observer [true/false]?" << endl;
        cin >> boolalpha >> phaseObserver;
    } while (cin.fail());

    do {
        cin.clear();
        statisticsObserver = false;
        // discard 'bad' character(s)
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ok last step, do you want to turn on the statistics observer [true/false]?" << endl;
        cin >> boolalpha >> statisticsObserver;
    } while (cin.fail());
}

void GameInitialization::gameStart() {
    selectMap();
    selectPlayerNumber();
    setupObservers();

    setupPlayers();
    setupOrders();
    assignCards();

}

Map *GameInitialization::getMap() const {
    return map;
}

void GameInitialization::setMap(Map *map) {
    GameInitialization::map = map;
}

Deck *GameInitialization::getDeck() const {
    return deck;
}

void GameInitialization::setDeck(Deck *deck) {
    GameInitialization::deck = deck;
}

const vector<Player *> &GameInitialization::getPlayers() const {
    return players;
}

void GameInitialization::setPlayers(const vector<Player *> &players) {
    GameInitialization::players = players;
}

const vector<string> &GameInitialization::getAvailableMaps() const {
    return availableMaps;
}

void GameInitialization::setAvailableMaps1(const vector<string> &availableMaps) {
    GameInitialization::availableMaps = availableMaps;
}

bool GameInitialization::isPhaseObserver() const {
    return phaseObserver;
}

void GameInitialization::setPhaseObserver(bool phaseObserver) {
    GameInitialization::phaseObserver = phaseObserver;
}

bool GameInitialization::isStatisticsObserver() const {
    return statisticsObserver;
}

void GameInitialization::setStatisticsObserver(bool statisticsObserver) {
    GameInitialization::statisticsObserver = statisticsObserver;
}

int GameInitialization::getNumPlayer() const {
    return numPlayer;
}

void GameInitialization::setNumPlayer(int numPlayer) {
    GameInitialization::numPlayer = numPlayer;
}

void GameInitialization::setupPlayers() {

    for (int i = 0; i < this->getNumPlayer(); i++) {
        this->players.push_back(new Player());
    }
}

void GameInitialization::setupOrders() {
    for (auto player : players) {
        player->setOrders(new OrdersList());
    }
}

void GameInitialization::assignCards() {

    this->deck = new Deck(50);
    for (auto player : players) {
        player->setHandOfCards(new Hand());
    }
}

//GAME STARTUP PHASE

GameSetup::GameSetup(vector<Player *> oderOfPlayer, Map *map) {
    this->oderOfPlayer = oderOfPlayer;
    this->map = map;
}

void GameSetup::startupPhase() {
    randomlySetOrder();
    assignCountriesToPlayers();
    assignArmiesToPlayers();
}

void GameSetup::randomlySetOrder() {

    cout << "Before shuffling, this is the order of players" << endl;
    for (auto &it : oderOfPlayer)
        std::cout << ' ' << it;

    shuffle(oderOfPlayer.begin(), oderOfPlayer.end(), std::mt19937(std::random_device()()));

    cout << "After shuffling, this is the order of players" << endl;
    for (auto &it : oderOfPlayer)
        std::cout << ' ' << it;

}

void GameSetup::assignCountriesToPlayers() {
    int territoriesAssigned = 0;
    vector<Territory *> territoriesAvailable = map->getTerritoryList();

    while (!territoriesAvailable.empty()) {
        int randomIndex = rand() % territoriesAvailable.size();
        Territory *territory = territoriesAvailable.at(randomIndex);
        //remove it from available territories
        territoriesAvailable.erase(territoriesAvailable.begin() + randomIndex);
        oderOfPlayer.at(territoriesAssigned % oderOfPlayer.size())->addTerritory(territory);
        cout << "assigning territory " << territory->getTerritoryName() << " to "
             << oderOfPlayer.at(territoriesAssigned % oderOfPlayer.size()) << endl;
        territoriesAssigned++;
    }
}

void GameSetup::assignArmiesToPlayers() {
    int nmbArmy = getInitialArmyNumber();
    for (auto p : this->oderOfPlayer) {
        p->setNumberOfArmies(nmbArmy);
    }
}

int GameSetup::getInitialArmyNumber() {
    switch (this->oderOfPlayer.size()) {
        case 2:
            return 40;
        case 3:
            return 35;
        case 4:
            return 30;
        case 5:
            return 25;
    }
}



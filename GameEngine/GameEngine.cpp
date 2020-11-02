#include <fstream>
#include "GameEngine.h"
#include "../MapLoader/MapLoader.h"
#include "../Player/Player.h"
#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::__fs::filesystem;


GameEngine::GameEngine(Map *map, Deck *deck, vector<Player *> &players) : map(map), deck(deck),
                                                                          players(players) {}


void GameSetup::selectMap() {
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

void GameSetup::setAvailableMaps(const string &path) {
    for (const auto &entry : fs::directory_iterator(path))
        if (!entry.is_directory())
            this->availableMaps.push_back(entry.path().filename());
}

void GameSetup::selectPlayerNumber() {
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

void GameSetup::setupObservers() {

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

void GameSetup::gameStart() {
    selectMap();
    selectPlayerNumber();
    setupObservers();

    setupPlayers();
    setupOrders();
    assignCards();

}

Map *GameSetup::getMap() const {
    return map;
}

void GameSetup::setMap(Map *map) {
    GameSetup::map = map;
}

Deck *GameSetup::getDeck() const {
    return deck;
}

void GameSetup::setDeck(Deck *deck) {
    GameSetup::deck = deck;
}

const vector<Player *> &GameSetup::getPlayers() const {
    return players;
}

void GameSetup::setPlayers(const vector<Player *> &players) {
    GameSetup::players = players;
}

const vector<string> &GameSetup::getAvailableMaps() const {
    return availableMaps;
}

void GameSetup::setAvailableMaps1(const vector<string> &availableMaps) {
    GameSetup::availableMaps = availableMaps;
}

bool GameSetup::isPhaseObserver() const {
    return phaseObserver;
}

void GameSetup::setPhaseObserver(bool phaseObserver) {
    GameSetup::phaseObserver = phaseObserver;
}

bool GameSetup::isStatisticsObserver() const {
    return statisticsObserver;
}

void GameSetup::setStatisticsObserver(bool statisticsObserver) {
    GameSetup::statisticsObserver = statisticsObserver;
}

int GameSetup::getNumPlayer() const {
    return numPlayer;
}

void GameSetup::setNumPlayer(int numPlayer) {
    GameSetup::numPlayer = numPlayer;
}

void GameSetup::setupPlayers() {

    for (int i = 0; i < this->getNumPlayer(); i++) {
        this->players.push_back(new Player());
    }
}

void GameSetup::setupOrders() {
    for (auto player : players) {
        player->setOrders(new OrdersList());
    }
}

void GameSetup::assignCards() {

    this->deck = new Deck(50);
    for (auto player : players) {
        player->setHandOfCards(new Hand());
    }
}



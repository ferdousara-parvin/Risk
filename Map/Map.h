#ifndef RISK_MAP_H
#define RISK_MAP_H

#include <vector>
#include <map>
#include <string>

using namespace std;

/**
 * This class represents a territory in the Risk game
 * A Territory represents any land that can be owned by a player.
 * Any territory must belong to a continent and have a name
 */
class Territory {
private:
    string territoryName;
    string owner; // until we have a Player object we will use string
    int continentId;
    int territoryId;
    int unitNbr;
    vector<Territory *> adjList;
public:
    Territory();

    Territory(const Territory &original);

    Territory& operator=(const Territory& otherTerritory);

    friend std::ostream &operator<<(std::ostream &stream, Territory &c);

    // Getters
    string getTerritoryName();

    string getOwner();

    int getTerritoryId();

    int getUnitNbr();

    vector<Territory *> &getAdjList();

    int getContinentId();

    // Setters
    void setTerritoryName(string territoryName);

    void setOwner(string owner);

    void setTerritoryId(int territoryId);

    void setUnitNbr(int unitNbr);

    void setContinentId(int continentId);

    void setAdjList(vector<Territory *> &adjList);

    // Adds an edge between two territories
    void addLink(Territory *n);
};

/**
 * This class represents a Continent in the risk game
 * A continent contains a list of territories inside the continent as well as a bonus for players that own all
 * territories inside this continent
 */
class Continent {
private:
    int continentId;
    int bonus;
    string continentName;
    vector<Territory *> territories;

    bool isSameOwner();

public:
    Continent();

    // copy constructor
    Continent(const Continent &original);

    Continent &operator=(const Continent &otherContinent);

    // output steam operator override
    friend std::ostream &operator<<(std::ostream &stream, Continent &c);

    // Getters
    int getContinentId();

    string getContinentName();

    int getBonus();

    string getOwner();

    vector<Territory *> &getTerritories();

    // Setters
    void setContinentId(int continentId);

    void setContinentName(string continentName);

    void setBonus(int bonus);

    void setTerritories(vector<Territory *> territories);
};

/**
 * This class represents a graph in the Risk game
 * A Graph is a list of connected Territories. In other words, it represents a list of countries
 * and continent that are interconnected with each other
 */
class Graph {
private:
    vector<Territory *> territoryList;

    vector<Continent *> continentList;

    // Used to validate if the graph is fully connected
    bool isGraphConnected();

    // Used to validate if the continents are connected
    bool isContinentSubgraphConnected();

    // Used to validate if each territory exists in exactly one continent.
    bool isTerritoryContinentUnique();

public:
    Graph();

    Graph(vector<Territory *> &territoryList, vector<Continent *> &continentList);

    // Copy Constructor
    Graph(const Graph &original);

    Graph &operator=(const Graph &otherGraph);

    friend std::ostream &operator<<(std::ostream &stream, Graph &c);

    // Getters
    vector<Territory *> &getTerritoryList();

    vector<Continent *> &getContinentList();

    // Setters
    void setTerritoryList(vector<Territory *> &territoryList);

    void setContinentList(vector<Continent *> &continentList);

    // Add continents individually
    void addContinent(Continent *continent);

    // Add territories individually
    void addTerritory(Territory *territory);

    // Used to validate the graph using the 3 defined conditions for connectivity.
    bool validate();
};

#endif
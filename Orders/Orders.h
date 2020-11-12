#ifndef RISK_ORDERS_H
#define RISK_ORDERS_H

#include <vector>
#include <iostream>
#include "../Map/Map.h"

using namespace std;

/**
 * This class represents an Order that a player can give for the Risk Game
 * The possible types of Orders are Deploy, Advance, Bomb, Blockade, Airlift, Negotiate.
 */
 // TODO: add Player field
class Order {
private:
    string description;

    int priority;

public:
    Order(string description, int priority);

    friend ostream &operator<<(ostream &stream, Order &order);

    // The following methods are pure virtual functions (must be overridden)
    /**
     * Checks if the Order given is a valid order.
     * @return boolean
     */
    virtual bool validate() = 0;

    /**
     * Executes the Order's actions.
     */
    virtual void execute() = 0;

    virtual void issue(Player* player) = 0;

    const string &getDescription() const;

    int getPriority() const;

    virtual ~Order();
};

/**
 * Places some armies on one of the current player’s territories.
 */
class DeployOrder : public Order {
public:
    DeployOrder();

    DeployOrder(const DeployOrder &original);

    DeployOrder &operator=(const DeployOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:
    Territory *targetTerritory;

    int numberOfArmiesToDeploy;

    bool validate() override;
};

/**
 * Move some armies from one of the current player’s territories (source) to an adjacent territory
 * (target). If the target territory belongs to the current player, the armies are moved to the target
 * territory. If the target territory belongs to another player, an attack happens between the two
 * territories.
 */
class AdvanceOrder : public Order {
public:
    AdvanceOrder();

    AdvanceOrder(const AdvanceOrder &original);

    AdvanceOrder &operator=(const AdvanceOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:
    Territory *sourceTerritory;
    Territory *targetTerritory;
    int numberOfArmiesToAdvance;

    bool validate() override;
};

/**
 * Destroy half of the armies located on an opponent’s territory that is adjacent to one of the current
 * player’s territories.
 */
class BombOrder : public Order {
public:
    BombOrder();

    BombOrder(const BombOrder &original);

    BombOrder &operator=(const BombOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:
    Territory* targetTerritory;

    bool validate() override;
};

/**
 * Triple the number of armies on one of the current player’s territories and make it a neutral territory
 */
class BlockadeOrder : public Order {
public:
    BlockadeOrder();

    BlockadeOrder(const BlockadeOrder &original);

    BlockadeOrder &operator=(const BlockadeOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:

    Territory *targetTerritory;

    bool validate() override;

};

/**
 * Advance some armies from one of the current player’s territories to any another territory.
 */
class AirliftOrder : public Order {
public:
    AirliftOrder();

    AirliftOrder(const AirliftOrder &original);

    AirliftOrder &operator=(const AirliftOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:
    Territory *sourceTerritory;
    Territory *targetTerritory;

    int numberOfArmiesToAirlift;

    bool validate() override;

};

/**
 * Prevent attacks between the current player and another player until the end of the turn.
 */
class NegotiateOrder : public Order {
public:
    NegotiateOrder();

    NegotiateOrder(const NegotiateOrder &original);

    NegotiateOrder &operator=(const NegotiateOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:
    Player* targetPlayer;

    bool validate() override;
};

class ReinforcementOrder : public Order {
public:
    ReinforcementOrder();

    ReinforcementOrder(const ReinforcementOrder &original);

    ReinforcementOrder &operator=(const ReinforcementOrder &order);

    void execute() override;

    void issue(Player* player) override;

private:

    bool validate() override;
};

/**
 * This class represents a list of orders for the Risk game
 * An OrdersList is a list of Orders that can be Deploy, Advance, Bomb, Blockade, Airlift, Negotiate, Reinforce.
 */
class OrdersList {

private:
    vector<Order *> orderList;

    /**
     * Helper method used to create a deep copy of an existing vector of Order *. Useful for the copy constructor and
     * the assignment operator.
     * @param originalVector: vector whose contents will be copied
     * @param destinationVector: vector which will be updated with the copies
     */
    static void copyOrderList(const vector<Order *> &originalVector, vector<Order *> &destinationVector);

public:
    OrdersList();

    ~OrdersList();

    OrdersList(const OrdersList &original);

    OrdersList &operator=(const OrdersList &original);

    friend ostream &operator<<(ostream &stream, OrdersList &ordersList);

    /**
     * Adds an Order to the list of Orders
     * @param order
     */
    void add(Order *order);

    /**
     * Deletes an Order from the list of Orders
     * @param order
     * @return boolean indicating order removed successfully
     */
    bool remove(Order *order);

    /**
     * Moves an order to the given destination index
     * @param order
     * @param destination
     * @return boolean indicating if move was successful
     */
    bool move(Order *order, int destination);

    vector<Order *> &getOrderList();

    void sortOrderListByPriority();
};

#endif //RISK_ORDERS_H

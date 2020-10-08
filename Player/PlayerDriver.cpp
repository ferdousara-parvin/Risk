#include <iostream>
#include "Player.h"

int main() {

    cout << "Setting Up.." << endl;

    // Create Territories and their Adjacent Territories
    Territory *t1 = new Territory();
    t1->setTerritoryName("Territory 1");
    Territory *t2 = new Territory();
    t2->setTerritoryName("Territory 2");
    Territory *t3 = new Territory();
    t3->setTerritoryName("Territory 3");
    Territory *t4 = new Territory();
    t4->setTerritoryName("Territory 4");
    Territory *t5 = new Territory();
    t5->setTerritoryName("Territory 5");

    t1->getAdjList().push_back(t3);
    t1->getAdjList().push_back(t4);
    t1->getAdjList().push_back(t2);

    t2->getAdjList().push_back(t1);
    t2->getAdjList().push_back(t3);

    t3->getAdjList().push_back(t1);
    t3->getAdjList().push_back(t2);
    t3->getAdjList().push_back(t4);

    t4->getAdjList().push_back(t1);
    t4->getAdjList().push_back(t3);
    t4->getAdjList().push_back(t5);

    t5->getAdjList().push_back(t4);

    vector<Territory *> territoriesOwnedP1;
    territoriesOwnedP1.push_back(t1);
    territoriesOwnedP1.push_back(t2);

    vector<Territory *> territoriesOwnedP2;
    territoriesOwnedP2.push_back(t3);
    territoriesOwnedP2.push_back(t4);
    territoriesOwnedP2.push_back(t5);

    // Create Hand
    Deck *deck = new Deck(10);
    vector<Card *> cardsP1;
    cardsP1.push_back(deck->draw());
    cardsP1.push_back(deck->draw());
    cardsP1.push_back(deck->draw());
    Hand *handP1 = new Hand(cardsP1);

    vector<Card *> cardsP2;
    cardsP2.push_back(deck->draw());
    cardsP2.push_back(deck->draw());
    cardsP2.push_back(deck->draw());
    Hand *handP2 = new Hand(cardsP2);

    cout << "Creating Player 1..\n" << endl;
    Player* p1 = new Player();
    p1->setPlayerName("Player 1");
    p1->setTerritories(territoriesOwnedP1);
    p1->setHandOfCards(handP1);
//    cout << *p1 << endl;

    cout << "Creating Player 2..\n" << endl;
    Player* p2 = new Player();
    p2->setPlayerName("Player 2");
    p2->setTerritories(territoriesOwnedP2);
    p2->setHandOfCards(handP2);
//    cout << *p2 << endl;

    cout << "Executing toDefend()..\n" << endl;

    vector<Territory *> toDefendP1 = p1->toDefend();
    cout << "Territories to defend by Player 1\n" << endl;
    for(Territory* territory: toDefendP1) {
        cout << *territory << endl;
    }
    vector<Territory *> toDefendP2 = p2->toDefend();
    cout << "Territories to defend by Player 2\n" << endl;
    for(Territory* territory: toDefendP2) {
        cout << *territory << endl;
    }

    cout << "Executing toAttack()..\n" << endl;

    vector<Territory *> toAttackP1 = p1->toAttack();
    cout << "Territories to attack by Player 1\n" << endl;
    for(Territory* territory: toAttackP1) {
        cout << *territory << endl;
    }

    vector<Territory *> toAttackP2 = p2->toAttack();
    cout << "Territories to attack by Player 2\n" << endl;
    for(Territory* territory: toAttackP2) {
        cout << *territory << endl;
    }

    cout << "Executing issueOrder().." << endl;
    p1->issueOrder();
    p2->issueOrder();

    cout << "Execution of Player Terminated" << endl;
}

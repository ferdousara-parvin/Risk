#include "Cards.h"
#include "../GameEngine/GameEngine.h"
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>

using namespace std;

/**
 * Card class
**/
Card::Card(CardType type) : type(type) {}

Card::Card(const Card &original) {
    type = original.type;
}

Card &Card::operator=(const Card &otherCard) {
    type = otherCard.type;
    return *this;
}

ostream &operator<<(ostream &stream, const Card &c) {
    return stream << "Information on Card object: " << endl
                  << "Card type: " << c.type << endl;
}

// TODO: remove cout
// Orders are deleted when players are deleted since they reside in the player's orders list
Order *Card::play() {
    Order *order;
    switch (type) {
        case CardType::bomb:
            order = new BombOrder();
            cout << "play(): played bomb " << endl;
            break;
        case CardType::reinforcement:
            order = nullptr;
            cout << "play(): played reinforcement " << endl;
            break;
        case CardType::blockade:
            order = new BlockadeOrder();
            cout << "play(): played blockade " << endl;
            break;
        case CardType::airlift:
            order = new AirliftOrder();
            cout << "play(): played airlift " << endl;
            break;
        case CardType::diplomacy:
            order = new NegotiateOrder();
            cout << "play(): played diplomacy " << endl;
            break;
    }
    return order;
}

Card::CardType Card::getType() const {
    return type;
}

void Card::setType(Card::CardType type) {
    Card::type = type;
}

/**
 * Deck class
 */
Deck::Deck(int size) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < (size/5); j++) {
            switch (i) {
                case 0:
                    cards.push_back(new Card(Card::bomb));
                    break;
                case 1:
                    cards.push_back(new Card(Card::reinforcement));
                    break;
                case 2:
                    cards.push_back(new Card(Card::blockade));
                    break;
                case 3:
                    cards.push_back(new Card(Card::airlift));
                    break;
                case 4:
                    cards.push_back(new Card(Card::diplomacy));
                    break;
            }
        }
    }
    shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
}

Deck::Deck(const Deck &original) {
    cards = vector<Card *>(original.cards.size());
    for (int i = 0; i < cards.size(); i++)
        cards[i] = new Card(*original.cards[i]);
}

Deck::~Deck() {
    for (auto p : cards) {
        delete p;
        cout << "deleted card in deck" << endl;
        p = nullptr;
    }
}

Deck &Deck::operator=(const Deck &otherDeck) {
    cards = vector<Card *>(otherDeck.cards.size());
    for (int i = 0; i < cards.size(); i++)
        cards[i] = new Card(*otherDeck.cards[i]);
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Deck &d) {
    return stream << "Information on Deck object:" << endl
                  << "Number of cards in deck: " << d.getCards().size() << endl;
}

const vector<Card *> &Deck::getCards() const {
    return cards;
}

void Deck::setCards(const vector<Card *> &cards) {
    Deck::cards = cards;
}

Card *Deck::draw() {
    if (cards.empty())
        return nullptr;
    int randomIndex = rand() % cards.size();
    Card *card = cards.at(randomIndex);
    cards.erase(cards.begin() + randomIndex);
    return card;
}

void Deck::addCard(Card *card) {
    cards.push_back(card);
}

/**
 * Hand class
 */
Hand::Hand() : cards() {}

Hand::Hand(vector<Card *> cards) : cards(cards) {}

Hand::Hand(const Hand &original) {
    cards = vector<Card *>(original.getCards().size());
    for (int i = 0; i < cards.size(); i++)
        cards[i] = new Card(*original.getCards().at(i));
}

Hand &Hand::operator=(const Hand &otherHand) {
    cards = vector<Card *>(otherHand.getCards().size());
    for (int i = 0; i < cards.size(); i++)
        cards[i] = new Card(*otherHand.getCards().at(i));
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Hand &h) {
    return stream << "Information on Hand object:" << endl
                  << "Number of cards in Hand: " << h.getCards().size() << endl;
}

Hand::~Hand() {
    for (auto p : cards) {
        cout << "deleted card in hand" << endl;
        delete p;
        p = nullptr;
    }
}

const vector<Card *> &Hand::getCards() const {
    return cards;
}

void Hand::setCards(const vector<Card *> &cards) {
    Hand::cards = cards;
}

void Hand::addCard(Card *card) {
    cards.push_back(card);
}

bool Hand::removeCard(Card* card) {
    auto position = find(cards.begin(), cards.end(), card);
    if (position != cards.end()) {
        GameEngine::getInstance()->getDeck()->addCard(card);
        cards.erase(position);
        return true;
    }
    cout << "Error removing card from hand." << endl;
    return false;
}


int Hand::getAmountOfCardsOfType(Card::CardType type) {
    int counter = 0;
    for (Card *card: cards)
        if (card->getType() == type) counter++;

    return counter;
}

Card *Hand::getNextCard() {
    Card *cardChosen = nullptr;
    for (Card *card: cards) {
        if (card->getType() != Card::CardType::reinforcement)
            cardChosen = card;
    }

    return cardChosen;
}

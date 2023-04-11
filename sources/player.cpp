//
// Created by israel on 3/25/23.
//

#include "player.hpp"

using namespace ariel;

Player::Player(string name) {
    this->name=name;
    this->winsNum=0;
    this->CardsStack = vector<Card>();
    this->Taken = vector<Card>();
}

void Player::pushCardsStack(const Card& c){this->CardsStack.push_back(c);}

void Player::pushTaken(const Card& c){this->Taken.push_back(c);}

Card Player::popCardsStack(){
    Card c = this->CardsStack.back();
    this->CardsStack.pop_back();
    return c;
}

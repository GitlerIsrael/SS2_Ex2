#pragma once
#include <iostream>
#include "vector"
#include "card.hpp"
using namespace std;

namespace ariel{
    class Player{
    private:
        string name;
        int winsNum;
        vector<Card> CardsStack;
        vector<Card> Taken;
    public:
        //defined inline
        string getName() { return this->name; }
        double getWinsNum() const {return this->winsNum;}
        int stacksize() const {return static_cast<int>(CardsStack.size());}
        int cardesTaken() const {return static_cast<int>(Taken.size());}
        void incrementWinsNum(){this->winsNum+=1;}
        //outline
        void pushCardsStack(const Card& card);
        Card popCardsStack();
        void pushTaken(const Card& card);

        //constructor-
        explicit Player(string name);
    };
}
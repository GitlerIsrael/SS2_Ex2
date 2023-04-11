#pragma once
#include "player.hpp"
#include <iostream>

using namespace std;

namespace ariel{
    class Game{
    private:
        Player& player1;
        Player& player2;
        vector<string> Turns;
        vector<Card> deck;
        int turnsNum;
        int drawsNum;

    public:
        //inline
        double getTurnsNum() const{return this->turnsNum;}
        double getDrawsNum() const{return this->drawsNum;}
        void incrementTurnsNum(){turnsNum+=1;}
        void incrementDrawsNum(){drawsNum+=1;}

        //outline
        void spreadCardsBeginning();
        void spreadCardsDraw();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        Game(Player& pl1, Player& pl2);
    };
}
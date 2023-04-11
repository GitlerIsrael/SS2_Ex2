//
// Created by israel on 3/25/23.
//
#include <algorithm>
#include <random>
#include <chrono>
#include "game.hpp"
using namespace ariel;
using namespace std;


Game::Game(Player& pl1, Player& pl2):player1(pl1), player2(pl2){
    this->turnsNum=0;
    this->drawsNum=0;
    this->Turns = vector<string>();
    this->deck = vector<Card>();
    // Create the deck of cards
    for (int i = 2; i <= 14; i++) {
        deck.push_back({"Hearts",i});
        deck.push_back({"Diamonds", i});
        deck.push_back({"Clubs", i});
        deck.push_back({"Spades", i});
    }

    // Shuffle the deck
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
    spreadCardsBeginning();
}

void Game::spreadCardsBeginning() {
    size_t deckSize = deck.size();
    for (int i = 0; i < deckSize; i++) {
        if (i % 2 == 0) {
            this->player1.pushCardsStack(deck.back());
            deck.pop_back();
        } else {
            this->player2.pushCardsStack(deck.back());
            deck.pop_back();
        }
    }
}

void Game::spreadCardsDraw() {
    for (int i = 0; i < deck.size(); i++) {
        if (i % 2 == 0) {
            this->player1.pushTaken(deck.back());
            deck.pop_back();
        } else {
            this->player2.pushTaken(deck.back());
            deck.pop_back();
        }
    }
}

void Game::playTurn(){
    if(&player1==&player2){
        throw "Can't play with yourself...";
    }
    if(player1.stacksize()!=0) {

        Card cp1 = player1.popCardsStack();
        Card cp2 = player2.popCardsStack();

        //player number 1 won this turn
        if ((cp2.getCardNumber()!=2 && cp1.getCardNumber() > cp2.getCardNumber())  ||
        (cp1.getCardNumber()!=14 && cp1.getCardNumber() > cp2.getCardNumber()) ||
        (cp1.getCardNumber()==2 && cp2.getCardNumber()==14)) {
            this->incrementTurnsNum();
            player1.incrementWinsNum();
            //deck holds now all cards from draw if happened
            for(Card c:deck){
                player1.pushTaken(deck.back());
                deck.pop_back();
            }
            player1.pushTaken(cp1);
            player1.pushTaken(cp2);
            this->Turns.push_back(
                    player1.getName() + " played " + cp1.toString() + " " + player2.getName() + " played " + cp2.toString() + ". " +
                    player1.getName() + " wins.");

        }
        //player number 2 won this turn
        else if ((cp1.getCardNumber()!=2 && cp2.getCardNumber() > cp1.getCardNumber())  ||
                 (cp2.getCardNumber()!=14 && cp2.getCardNumber() > cp1.getCardNumber()) ||
                 (cp2.getCardNumber()==2 && cp1.getCardNumber()==14)) {
            this->incrementTurnsNum();
            player2.incrementWinsNum();
            for(Card c:deck){ //deck holds now all cards from draw if happened
                player2.pushTaken(deck.back());
                deck.pop_back();
            }
            player2.pushTaken(cp1);
            player2.pushTaken(cp2);
            this->Turns.push_back(
                    player1.getName() + " played " + cp1.toString() + " " + player2.getName() + " played " + cp2.toString() + ". " +
                    player2.getName() + " wins.");
        }
        //Draw
        else{
            this->incrementDrawsNum();
            this->Turns.push_back(
                    player1.getName() + " played " + cp1.toString() + " " + player2.getName() + " played " + cp2.toString() + ". " +
                    "Draw");
            if(player1.stacksize()>=2){ //Cards values are equal and have enough cards for draw.
                this->deck.push_back(cp1);
                this->deck.push_back(cp2);
                this->deck.push_back(player1.popCardsStack());
                this->deck.push_back(player2.popCardsStack());
                playTurn();
            }
            else if(player1.stacksize()==1){
                this->incrementTurnsNum();
                spreadCardsDraw();
                player1.pushTaken(player1.popCardsStack());
                player2.pushTaken(player2.popCardsStack());
            }
            else{  //stackSize == 0
                this->incrementTurnsNum();
                spreadCardsDraw();
            }
        }
    } else {
        cout << "End of game!" <<endl;
        throw "Can't play another turn. the game is over";
    }
}
void Game::printLastTurn(){
    cout << this->Turns[this->Turns.size()-1] << endl;
}
void Game::playAll(){
    while(player1.stacksize()!=0){
        playTurn();
    }
}
void Game::printWiner(){
    if(player1.stacksize()==0){
        if(player1.cardesTaken() > player2.cardesTaken()){
            cout << player1.getName() << endl;
        } else if(player1.cardesTaken() < player2.cardesTaken()){
            cout << player2.getName() << endl;
        }else{
            cout << "TEKO" <<endl;
        }
    }else{
        cout << "The game still not over..." << endl;
    }
}
void Game::printLog(){
    for(const string& turn:this->Turns){
        cout << turn << endl;
    }
}
void Game::printStats(){
    cout << "Player1:" <<endl;
    cout << "Win rate: " << player1.getWinsNum()/this->getTurnsNum() << endl;
    cout << "Cards won: " << player1.cardesTaken() << "\n" << endl;

    cout << "Player2:" <<endl;
    cout << "Win rate: " << player2.getWinsNum()/this->getTurnsNum() << endl;
    cout << "Cards won: " << player2.cardesTaken() << "\n" << endl;

    cout << "General:" <<endl;
    cout << "Draw rate: " << this->getDrawsNum()/this->getTurnsNum() << endl;
    cout << "Amount of draws: " << this->getDrawsNum() << endl;
}

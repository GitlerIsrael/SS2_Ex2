#pragma once
#include <iostream>
using namespace std;

namespace ariel{
    class Player{
    private:
        string name;
    public:
        //defined inline
        string getName() { return this->name; }
        int stacksize(){return 0;};
        int cardesTaken(){return 0;};
        //constructors-
        Player(string name) {
            this->name=name;
        }
        Player(){};
//        ~Player();
    };
}
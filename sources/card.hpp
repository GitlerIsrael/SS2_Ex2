#pragma once
#include <iostream>
using namespace std;

class Card{
private:
    string shape;
    int number;
public:
    //defined inline
    int getCardNumber() const{return this->number;}

    string toString();
    Card(string shape, int number);
};

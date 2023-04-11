//
// Created by israel on 3/25/23.
//

#include "card.hpp"

// "outline" constructor implementation:
Card::Card(string shape, int number) {
    this->shape=shape;
    this->number=number;
}
string Card::toString() {
if(this->number==11){return "Jack of " + this->shape;}
if(this->number==12){return "Queen of " + this->shape;}
if(this->number==13){return "King of " + this->shape;}
if(this->number==14){return "Ace of " + this->shape;}
else{return to_string(this->number) + " of " + this->shape;}
}


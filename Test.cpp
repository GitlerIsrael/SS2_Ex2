//
// Created by israel on 3/26/23.
//
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
using namespace ariel;


TEST_CASE("Initialize") {
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2);

    //check total cards is 52 at the beginning of the game.
    CHECK((p1.stacksize() + p2.stacksize() == 52));

    //check each player has 26 card in the beginning of the game and 0 cards taken.
    CHECK((p1.stacksize() == 26));
    CHECK((p1.cardesTaken() == 0));

    CHECK((p2.stacksize() == 26));
    CHECK((p2.cardesTaken() == 0));
}

TEST_CASE("Initialize with same player as 2 players") {
    Player p("Bob");
    //check if throws exception while trying to initialize game with one player as 2 players.
    CHECK_THROWS(Game{p, p});
}

TEST_CASE("A player can only play in one game") {
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Evgeny");

    //check if throws exception while trying to initialize 2 games with the same player (a player can play in only one game).
    Game game(p1,p2);
    CHECK_THROWS(Game{p1, p3});
}

TEST_CASE("Playing process") {
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);

    //check if throws exception while trying to get the winner in the beginning of the game (there is no winner).
    CHECK_THROWS(game.printWiner());
    //check if throws exception while trying to print last turn in the beginning of the game (there is no last turn).
    CHECK_THROWS(game.printLastTurn());

    //play 5 turns
    for (int i = 0; i < 5; i++) {
        game.playTurn();
    }

    //check amount of cards after 5 turns.
    CHECK((p1.stacksize() <= 21)); //less than 21 if a draw was played.
    CHECK((p2.stacksize() <= 21));
    CHECK((p1.cardesTaken() >=5 || p2.cardesTaken() >=5));

    //check print func not throw exception.
    CHECK_NOTHROW(game.printLastTurn());
}

TEST_CASE("At most 26 turns") {
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1, p2);

    int counter = 0;
    for (int i = 0; i < 26; i++)
    {
        game.playTurn();
        counter++;
        if(p1.stacksize() == 0) //(or "p2.stacksize() == 0". its the same because they will be ZERO together)
            break;
    }
    //check there are maximum 26 turns in the game.
    CHECK((counter <= 26));
}

TEST_CASE("End of game") {
    Player p1("Alice");
    Player p2("Bob");

    Game game(p1,p2);
    game.playAll();

    //check that in the end of the game each of players remained with ZERO cards
    CHECK((p1.stacksize() == 0));
    CHECK((p2.stacksize() == 0));

    //check that we don't lost any card while the game and there are still 52 cards total
    CHECK((p1.cardesTaken() + p2.cardesTaken() == 52));


    //check that all print functions works well and not throw any exceptions
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
}
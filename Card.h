#pragma once
#include <string>
#include <iostream>
#include "Location.h"

// Forward declaration of Arena to avoid circular dependencies
class Arena;

// main abstract base class for all cards 
class Card
{
protected:
    string cardName;
    int elixirCost;

public:
    Card(std::string name, int cost)
        : cardName(name), elixirCost(cost) {}

    virtual ~Card() {}

    // getters
    string getCardName() const { return cardName; }
    int getElixirCost() const { return elixirCost; }

    virtual void deploy(Arena &arena, Location loc) = 0;
};
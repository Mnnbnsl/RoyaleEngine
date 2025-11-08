// Card.h
#pragma once
#include <string>
#include <iostream>
#include "Location.h"

// Forward declare Arena to break circular include
class Arena;

// Base class for all cards (troops, buildings, etc.)
class Card
{
protected:
    std::string cardName;  // Card's display name
    int elixirCost;        // Cost to play

public:
    Card(std::string name, int cost)
        : cardName(name), elixirCost(cost) {}

    virtual ~Card() {}

    // Simple getters
    std::string getCardName() const { return cardName; }
    int getElixirCost() const { return elixirCost; }

    // Must be implemented by child classes
    virtual void deploy(Arena &arena, Location loc) = 0;
};
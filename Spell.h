#pragma once
#include "Card.h"

// Forward declaration
class Arena;

/**
 * @class Spell
 * @brief Abstract class for all "Spell" type cards.
 * Inherits from Card.
 */
class Spell : public Card {
public:
    Spell(std::string name, int cost)
        : Card(name, cost) {} // Pass info up to the Card constructor

    virtual ~Spell() {}

    /**
     * All spells must implement deploy.
     * This is still pure virtual, so Spell remains an abstract class.
     */
    virtual void deploy(Arena& arena, Location loc) = 0;
};
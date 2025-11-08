#pragma once
#include "Card.h"
#include "IDamageable.h"
#include "Location.h"

// Forward declaration
class Arena;

/**
 * @class Building
 * @brief Abstract class for all "Building" type cards.
 * Inherits from Card and implements IDamageable.
 */
class Building : public Card, public IDamageable {
private:
    int maxHealth;
    int health;
    int lifetime; // e.g., in seconds or ticks
    Location location;

public:
    Building(std::string name, int cost, int maxHealth, int lifetime)
        : Card(name, cost),
          maxHealth(maxHealth),
          health(maxHealth),
          lifetime(lifetime) {}

    virtual ~Building() {}

    // --- Implementation of IDamageable interface ---
    void takeDamage(int amount) override {
        this->health -= amount;
        if (this->health < 0) this->health = 0;
        std::cout << this->Card::getCardName() << " takes " << amount << " damage, "
                  << this->health << " HP left." << std::endl;
    }

    int getHealth() const override { return health; }
    bool isAlive() const override { return this->health > 0 && this->lifetime > 0; }

    // --- Implementation of Card's abstract method ---
    void deploy(Arena& arena, Location loc) override {
        this->location = loc;
        std::cout << this->Card::getCardName() << " deployed at " << loc.toString() << std::endl;
        // In a real game: arena.addBuilding(this);
    }
    
    // --- Building-specific methods ---
    Location getLocation() const { return location; }

    /**
     * @return The character symbol for drawing this building.
     */
    virtual char getSymbol() const = 0; // Pure virtual
};
// Building.h
#pragma once
#include "Card.h"
#include "IDamageable.h"
#include "Location.h"

class Arena;

class Building : public Card, public IDamageable {
private:
    int maxHealth;
    int health;
    int lifetime; // We're not using this yet, but it's good design
    Location location;

public:
    Building(std::string name, int cost, int maxHealth, int lifetime)
        : Card(name, cost),
          maxHealth(maxHealth),
          health(maxHealth),
          lifetime(lifetime) {}

    virtual ~Building() {}

    // --- Implementation of IDamageable ---
    void takeDamage(int amount) override {
        this->health -= amount;
        if (this->health < 0) this->health = 0;
        // This is silent, as requested
    }

    int getHealth() const override { return health; }
    bool isAlive() const override { return this->health > 0; } // Simplified for now

    // --- Implementation of Card ---
    void deploy(Arena& arena, Location loc) override {
        this->location = loc;
        std::cout << this->Card::getCardName() << " deployed at " << loc.toString() << std::endl;
        // The main.cpp will call arena.addBuilding(this)
    }
    
    Location getLocation() const override { return location; }
    
    virtual std::string getCardName() const override {
        return Card::getCardName();
    }
    // --- UPDATED ---
    /**
     * @brief The "brain" of the building (e.g., to attack targets).
     * This is now pure virtual, just like in the Troop class.
     */
    virtual void act(Arena& arena) = 0;

    /**
     * @return The character symbol for drawing this building.
     */
    virtual char getSymbol() const = 0;
};
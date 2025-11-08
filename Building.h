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
    int lifetime;
    Location location;

public:
    Building(std::string name, int cost, int maxHealth, int lifetime)
        : Card(name, cost),
          maxHealth(maxHealth),
          health(maxHealth),
          lifetime(lifetime) {}

    virtual ~Building() {}

    // --- IDamageable interface ---
    void takeDamage(int amount) override {
        this->health -= amount;
        if (this->health < 0) this->health = 0;
    }

    int getHealth() const override { return health; }
    bool isAlive() const override { return this->health > 0; }

    // --- Card interface ---
    void deploy(Arena& arena, Location loc) override {
        this->location = loc;
        std::cout << this->Card::getCardName() << " deployed at " << loc.toString() << std::endl;
    }
    
    Location getLocation() const override { return location; }
    
    virtual std::string getCardName() const override {
        return Card::getCardName();
    }

    // --- Building behavior ---
    virtual void act(Arena& arena) = 0;  // Pure virtual - each building decides what to do

    virtual char getSymbol() const = 0;  // Symbol to show on the map
};
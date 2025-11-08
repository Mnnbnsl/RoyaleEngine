#pragma once
#include "Card.h"
#include "Location.h"
#include "IDamageable.h"

// Forward declaration
class Arena;

// Abstract base class for all troop type cards
class Troop : public Card, public IDamageable {
private:
    int maxHealth;
    int health;
    int damage;
    Location location;

public:
    Troop(std::string name, int elixir, int maxHealth, int damage)
        : Card(name, elixir),
          maxHealth(maxHealth),
          health(maxHealth),
          damage(damage),
          location(0, 0) {}

    virtual ~Troop() = default;

    // IDamageable interface
    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
        // // Optional: remove cout in production
        // std::cout << getCardName() << " takes " << damage 
        //           << " damage, " << health << " HP left.\n";
    }

    int getHealth() const override { return health; }
    bool isAlive() const override { return health > 0; }

    // Card interface
    void deploy(Arena& arena, Location loc) override {
        location = loc;
        // std::cout << getCardName() << " deployed at " 
        //           << loc.toString() << '\n';
        // Later: arena.addTroop(this);
    }

    // Troop-specific pure virtuals
    virtual void act(Arena& arena) = 0;
    virtual char getSymbol() const = 0;

    // Getters
    Location getLocation() const { return location; }
    int getDamage() const { return damage; }

protected:
    void setLocation(Location loc) { location = loc; }
};
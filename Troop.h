// Troop.h
#pragma once
#include "Card.h"
#include "IDamageable.h"
#include "Location.h"

class Arena;

class Troop : public Card, public IDamageable {
private: 
    int maxHealth;
    int health;
    int damage;
    Location location;

public:
    Troop(std::string name, int cost, int maxHealth, int damage)
        : Card(name, cost), 
          maxHealth(maxHealth), 
          health(maxHealth), 
          damage(damage),
          location(0, 0) {} 

    virtual ~Troop() {} 

    // --- UPDATED ---
    // This method is now "silent". It just changes the health.
    // The 'act' method will be responsible for reporting the damage.
    void takeDamage(int amount) override {
        this->health -= amount;
        if (this->health < 0) {
            this->health = 0;
        }
    }

    int getHealth() const override { return health; }
    bool isAlive() const override { return this->health > 0; }

    void deploy(Arena& arena, Location loc) override {
        this->location = loc;
        std::cout << Card::getCardName() << " deployed at " << loc.toString() << std::endl;
        // This 'std::cout' is OK because deploy only happens once.
    }

    virtual std::string getCardName() const override {
        return Card::getCardName();
    }
    
    virtual void act(Arena& arena) = 0;
    virtual char getSymbol() const = 0;

    // --- UPDATED ---
    // This now implements the new method from IDamageable
    Location getLocation() const override { return location; }
    
    int getDamage() const { return damage; }

protected:
    void setLocation(Location loc) { this->location = loc; }
};
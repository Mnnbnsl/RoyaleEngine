#pragma once
#include "Building.h"
#include "Arena.h"
#include <iostream>
#include <string>

/**
 * @class Cannon
 * @brief A concrete implementation of a defensive Building.
 * It implements the 'act' method to shoot at nearby enemies.
 */
class Cannon : public Building {
private:
    const int ATTACK_RANGE = 5;
    const int DAMAGE = 100;

public:
    // Call the Building constructor with Cannon's stats
    Cannon() : Building("Cannon", 3, 300, 30) {} // 30-second lifetime (not used yet)
    virtual ~Cannon() {}

    // --- Implementation of Building's abstract methods ---
    
    char getSymbol() const override {
        return 'C';
    }

    /**
     * This is the Cannon's "brain" (Polymorphism in action!).
     * It finds the closest enemy and shoots if it's in range.
     * It does NOT move.
     */
    void act(Arena& arena) override {
        // AI Logic:
        // 1. Find a target
        IDamageable* target = arena.getClosestEnemy(this); // 'this' is the Cannon

        if (target != nullptr && target->isAlive()) {
            Location targetLoc = target->getLocation();
            Location currentLoc = this->getLocation();
            int distance = currentLoc.distanceTo(targetLoc);

            // 2. Check if in attack range
            if (distance <= ATTACK_RANGE) {
                // 3. Attack
                target->takeDamage(DAMAGE);

                std::string log = Card::getCardName() + " shoots " + target->getCardName() 
                                + " for " + std::to_string(DAMAGE) + " damage ("
                                + std::to_string(target->getHealth()) + " HP left).";
                arena.logEvent(log);
            }
            // 4. No "else" block: Cannons do not move.
        }
    }
};
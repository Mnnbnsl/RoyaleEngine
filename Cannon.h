// Cannon.h
#pragma once
#include "Building.h"
#include "Arena.h"
#include <iostream>
#include <string>

/**
 * @class Cannon - type of building
 * @brief Defensive building that shoots nearby enemies.
 */
class Cannon : public Building {
private:
    const int ATTACK_RANGE = 5;  // Max distance to hit
    const int DAMAGE = 100;      // Damage per shot

public:
    Cannon() : Building("Cannon", 3, 300, 30) {}  // name, cost, health, lifetime
    virtual ~Cannon() {}

    // Show 'C' on the map
    char getSymbol() const override {
        return 'C';
    }

    // Cannon's turn: find and shoot closest enemy
    void act(Arena& arena) override {
        IDamageable* target = arena.getClosestEnemy(this);

        if (target != nullptr && target->isAlive()) {
            Location targetLoc = target->getLocation();
            Location currentLoc = this->getLocation();
            int distance = currentLoc.distanceTo(targetLoc);

            if (distance <= ATTACK_RANGE) {
                target->takeDamage(DAMAGE);

                std::string log = Card::getCardName() + " shoots " + target->getCardName() 
                                + " for " + std::to_string(DAMAGE) + " damage ("
                                + std::to_string(target->getHealth()) + " HP left).";
                arena.logEvent(log);
            }
        }
    }
};
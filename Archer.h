// Archer.h
#pragma once
#include "Troop.h"
#include "Arena.h"
#include <iostream>
#include <string>     // For std::to_string

class Archer : public Troop {
private:
    const int ATTACK_RANGE = 5;

public:
    Archer() : Troop("Archer", 3, 250, 75) {}
    virtual ~Archer() {}

    char getSymbol() const override { return 'A'; }

    // --- UPDATED ---
    /**
     * Archer's "brain" also reports actions to the Arena's log.
     */
    void act(Arena& arena) override {
        IDamageable* target = arena.getClosestEnemy(this);

        if (target != nullptr && target->isAlive()) {
            Location targetLoc = target->getLocation();
            Location currentLoc = this->getLocation();
            int distance = currentLoc.distanceTo(targetLoc);

            if (distance <= ATTACK_RANGE) {
                // Attack
                int dmg = this->getDamage();
                target->takeDamage(dmg);

                std::string log = Troop::getCardName() + " shoots " + target->getCardName() 
                                + " for " + std::to_string(dmg) + " damage ("
                                + std::to_string(target->getHealth()) + " HP left).";
                arena.logEvent(log);

            } else {
                // Move
                int dx = targetLoc.getX() - currentLoc.getX();
                int dy = targetLoc.getY() - currentLoc.getY();
                Location newLoc = currentLoc;
                
                if (std::abs(dx) > std::abs(dy)) {
                    newLoc = Location(currentLoc.getX() + (dx > 0 ? 1 : -1), currentLoc.getY());
                } else if (dy != 0) {
                    newLoc = Location(currentLoc.getX(), currentLoc.getY() + (dy > 0 ? 1 : -1));
                }

                setLocation(newLoc);
                arena.logEvent(Troop::getCardName() + " moves to " + newLoc.toString());
            }
        }
    }
};
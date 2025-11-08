// Archer.h
#pragma once
#include "Troop.h"
#include "Arena.h"
#include <iostream>
#include <string>     

class Archer : public Troop {
private:
    const int ATTACK_RANGE = 5;  // Max distance to shoot

public:
    Archer() : Troop("Archer", 3, 250, 75) {}  // name, speed, health, damage
    virtual ~Archer() {}

    char getSymbol() const override { return 'A'; }  // Symbol on the board

    // Archer's "brain" also reports actions to the Arena's log.
    
    void act(Arena& arena) override {
        IDamageable* target = arena.getClosestEnemy(this);  // Find nearest enemy

        if (target != nullptr && target->isAlive()) {
            Location targetLoc = target->getLocation();
            Location currentLoc = this->getLocation();
            int distance = currentLoc.distanceTo(targetLoc);

            if (distance <= ATTACK_RANGE) {
                // Attack if in range
                int dmg = this->getDamage();
                target->takeDamage(dmg);

                std::string log = Troop::getCardName() + " shoots " + target->getCardName() 
                                + " for " + std::to_string(dmg) + " damage ("
                                + std::to_string(target->getHealth()) + " HP left).";
                arena.logEvent(log);

            } else {
                // Move closer
                int dx = targetLoc.getX() - currentLoc.getX();
                int dy = targetLoc.getY() - currentLoc.getY();
                Location newLoc = currentLoc;
                
                // Move horizontally if that's the bigger gap
                if (std::abs(dx) > std::abs(dy)) {
                    newLoc = Location(currentLoc.getX() + (dx > 0 ? 1 : -1), currentLoc.getY());
                } 
                // Otherwise move vertically
                else if (dy != 0) {
                    newLoc = Location(currentLoc.getX(), currentLoc.getY() + (dy > 0 ? 1 : -1));
                }

                setLocation(newLoc);
                arena.logEvent(Troop::getCardName() + " moves to " + newLoc.toString());
            }
        }
    }
};
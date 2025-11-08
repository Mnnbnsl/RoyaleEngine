// Knight.h
#pragma once
#include "Troop.h"
#include "Arena.h"
#include <iostream>
#include <string>    

class Knight : public Troop {
public:
    Knight() : Troop("Knight", 3, 1000, 150) {}
    virtual ~Knight() {}

    char getSymbol() const override { return 'K'; }
   
    // Knight's "brain" now reports actions to the Arena's log instead of printing directly to console.

    void act(Arena& arena) override {
        IDamageable* target = arena.getClosestEnemy(this);

        if (target != nullptr && target->isAlive()) {
            Location targetLoc = target->getLocation();
            Location currentLoc = this->getLocation();

            if (currentLoc.distanceTo(targetLoc) <= 1) {
                // Attack
                int dmg = this->getDamage();
                target->takeDamage(dmg);
                
                // Build a detailed log string
                std::string log = Troop::getCardName() + " attacks " + target->getCardName() 
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
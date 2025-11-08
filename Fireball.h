// Fireball.h
#pragma once
#include "Spell.h"
#include "Arena.h"
#include <iostream>

/**
 * @class Fireball - type of spell
 * @brief Area-damage spell that hits all enemies in a radius.
 */
class Fireball : public Spell {
private:
    const int DAMAGE = 200;   // Damage to each target
    const int RADIUS = 2;     // Area of effect size

public:
    Fireball() : Spell("Fireball", 4) {}
    virtual ~Fireball() {}

    // Deploy = explode: damage all enemies in radius, then vanish
    void deploy(Arena& arena, Location loc) override {
        std::cout << getCardName() << " explodes at " << loc.toString() << "!" << std::endl;
        
        auto targets = arena.getEnemiesInRadius(loc, RADIUS);

        for (IDamageable* target : targets) {
            if (target != nullptr && target->isAlive()) {
                std::cout << "Fireball hits!" << std::endl;
                target->takeDamage(DAMAGE);
            }
        }
    }
};
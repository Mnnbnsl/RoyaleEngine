#pragma once
#include "Spell.h"
#include "Arena.h"
#include <iostream>

/**
 * @class Fireball
 * @brief A concrete implementation of a damage Spell.
 */
class Fireball : public Spell {
private:
    const int DAMAGE = 200;
    const int RADIUS = 2; // Deals area-of-effect damage

public:
    Fireball() : Spell("Fireball", 4) {}
    virtual ~Fireball() {}

    /**
     * The Fireball's 'deploy' is its main action.
     * It finds all enemies in a radius and damages them, then disappears.
     */
    void deploy(Arena& arena, Location loc) override {
        std::cout << getCardName() << " explodes at " << loc.toString() << "!" << std::endl;
        
        // Get all enemies in the radius from the Arena
        auto targets = arena.getEnemiesInRadius(loc, RADIUS);

        for (IDamageable* target : targets) {
            if (target != nullptr && target->isAlive()) {
                std::cout << "Fireball hits!" << std::endl;
                target->takeDamage(DAMAGE);
            }
        }
        // After deploying, the spell is "done." It doesn't stay on the field.
    }
};
// Arena.h
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream> // For std::stringstream

#include "Troop.h"
#include "Building.h"
#include "IDamageable.h"
#include "Location.h"

class Arena {
private:
    int width;
    int height;
    std::vector<Troop*> troops;
    std::vector<Building*> buildings;
    std::vector<IDamageable*> allTargets;

    // --- NEW ---
    // A log to store events that happen each tick.
    std::vector<std::string> eventLog;

    void cleanupDeadObjects() {
        // This function is complex but correct. No changes needed.
        auto newEnd = std::remove_if(allTargets.begin(), allTargets.end(),
            [](const IDamageable* target) {
                if (!target->isAlive()) {
                    // Important: delete the object before removing its pointer
                    // delete target; // This is complex, let's stick to deleting in ~Arena
                    return true;
                }
                return false;
            });
        allTargets.erase(newEnd, allTargets.end());

        troops.erase(std::remove_if(troops.begin(), troops.end(),
            [](const Troop* t) { return !t->isAlive(); }), troops.end());
            
        buildings.erase(std::remove_if(buildings.begin(), buildings.end(),
            [](const Building* b) { return !b->isAlive(); }), buildings.end());
    }

public:
    Arena(int width, int height) : width(width), height(height) {
        std::cout << "Arena created (" << width << "x" << height << ")" << std::endl;
    }

    ~Arena() {
        std::cout << "Arena being destroyed. Cleaning up..." << std::endl;
        
        // --- UPDATED for safer cleanup ---
        // We must delete from allTargets, as it's the master list.
        // But we must first cast them back to their original type? No,
        // we can just delete the pointers from the original lists.
        for (Troop* t : troops) {
             delete t; 
        }
        for (Building* b : buildings) { 
            delete b; 
        }
        
        troops.clear();
        buildings.clear();
        allTargets.clear();
    }

    void addTroop(Troop* troop) {
        this->troops.push_back(troop);
        this->allTargets.push_back(troop);
    }

    void addBuilding(Building* building) {
        this->buildings.push_back(building);
        this->allTargets.push_back(building);
    }

    // --- NEW ---
    /**
     * @brief Public method for objects to log their actions.
     */
    void logEvent(const std::string& event) {
        eventLog.push_back(event);
    }

    // --- UPDATED ---
    void update() {
        // 1. Clear the log for the new tick
        eventLog.clear();
        std::cout << "--- TICK START ---" << std::endl; // This log is fine

        // 2. ** POLYMORPHISM **
        for (Troop* troop : troops) {
            if (troop->isAlive()) {
                troop->act(*this); // This will now call logEvent()
            }
        }
        
        // 3. Clean up
        cleanupDeadObjects();
    }

    // --- UPDATED ---
    /**
     * @brief Renders the grid, unit health, and event log.
     */
    void render() const {
        // 1. Create the grid
        std::vector<std::string> grid(height, std::string(width, '.'));

        // 2. Draw buildings
        for (const Building* b : buildings) {
            Location loc = b->getLocation();
            if (loc.getX() >= 0 && loc.getX() < width && loc.getY() >= 0 && loc.getY() < height) {
                grid[loc.getY()][loc.getX()] = b->getSymbol();
            }
        }
        
        // 3. Draw troops
        for (const Troop* t : troops) {
            Location loc = t->getLocation();
            if (loc.getX() >= 0 && loc.getX() < width && loc.getY() >= 0 && loc.getY() < height) {
                grid[loc.getY()][loc.getX()] = t->getSymbol();
            }
        }

        // 4. Print the grid
        std::cout << "+" << std::string(width, '-') << "+" << std::endl;
        for (int y = 0; y < height; ++y) {
            std::cout << "|" << grid[y] << "|" << std::endl;
        }
        std::cout << "+" << std::string(width, '-') << "+" << std::endl;

        // --- NEW: Print Health Status ---
        std::cout << "--- STATUS ---" << std::endl;
        for (const Troop* t : troops) {
            std::cout << "  " << t->Card::getCardName() << " HP: " << t->getHealth() << std::endl;
        }
        for (const Building* b : buildings) {
            std::cout << "  " << b->Card::getCardName() << " HP: " << b->getHealth() << std::endl;
        }
        
        // --- NEW: Print Event Log ---
        std::cout << "--- LOG ---" << std::endl;
        if (eventLog.empty()) {
            std::cout << "  (No actions)" << std::endl;
        }
        for (const std::string& event : eventLog) {
            std::cout << "  > " << event << std::endl;
        }
    }

    // --- AI Helper Methods (No changes needed) ---
    
    IDamageable* getClosestEnemy(const IDamageable* attacker) const {
        IDamageable* closestTarget = nullptr;
        int minDistance = std::numeric_limits<int>::max();
        Location attackerLoc = attacker->getLocation();

        // This loop checks *all* targets
        for (IDamageable* target : allTargets) {
            // Skip the target if it is the attacker itself.
            if (target == attacker) {
                continue; 
            }

            if (target->isAlive()) {
                int dist = attackerLoc.distanceTo(target->getLocation());
                if (dist < minDistance) {
                    minDistance = dist;
                    closestTarget = target;
                }
            }
        }
        return closestTarget;
    }

    std::vector<IDamageable*> getEnemiesInRadius(Location atLoc, int radius) const {
        std::vector<IDamageable*> targetsInRadius;
        for (IDamageable* target : allTargets) {
            if (target->isAlive()) {
                if (atLoc.distanceTo(target->getLocation()) <= radius) {
                    targetsInRadius.push_back(target);
                }
            }
        }
        return targetsInRadius;
    }
};
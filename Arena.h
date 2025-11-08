// Arena.h
#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <limits>
#include <algorithm>
#include <sstream> 

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
    std::vector<IDamageable*> allTargets;  // Master list for AI targeting

  
    // Stores events each tick for display
    std::vector<std::string> eventLog;

    // Remove dead units from all lists
    void cleanupDeadObjects() {
        // Erase-remove idiom: filter out dead targets
        auto newEnd = std::remove_if(allTargets.begin(), allTargets.end(),
            [](const IDamageable* target) {
                return !target->isAlive();  // Keep only alive ones
            });
        allTargets.erase(newEnd, allTargets.end());

        // Clean up troop and building lists separately
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
        
        // Delete actual objects from their original vectors
        for (Troop* t : troops)     { delete t; }
        for (Building* b : buildings) { delete b; }
        
        // Clear all containers
        troops.clear();
        buildings.clear();
        allTargets.clear();
    }

    void addTroop(Troop* troop) {
        troops.push_back(troop);
        allTargets.push_back(troop);  // So AI can see it
    }

    void addBuilding(Building* building) {
        buildings.push_back(building);
        allTargets.push_back(building);
    }

    // Let troops/buildings report what they did
    void logEvent(const std::string& event) {
        eventLog.push_back(event);
    }

    // Main game loop step
    void update() {
        eventLog.clear();  // Fresh log each turn

        // Let troops act (move/attack)
        for (Troop* troop : troops) {
            if (troop->isAlive()) {
                troop->act(*this);
            }
        }
        
        // Let buildings act (e.g., towers shoot)
        for (Building* building : buildings) {
            if (building->isAlive()) {
                building->act(*this);
            }
        }
        
        // Remove dead units
        cleanupDeadObjects();
    }

    // Draw the arena, status, and action log
    void render() const {
        // Build empty grid
        std::vector<std::string> grid(height, std::string(width, '.'));

        // Place buildings
        for (const Building* b : buildings) {
            Location loc = b->getLocation();
            if (loc.getX() >= 0 && loc.getX() < width && loc.getY() >= 0 && loc.getY() < height) {
                grid[loc.getY()][loc.getX()] = b->getSymbol();
            }
        }
        
        // Place troops (on top of buildings if overlap)
        for (const Troop* t : troops) {
            Location loc = t->getLocation();
            if (loc.getX() >= 0 && loc.getX() < width && loc.getY() >= 0 && loc.getY() < height) {
                grid[loc.getY()][loc.getX()] = t->getSymbol();
            }
        }

        // Print grid with borders
        std::cout << "+" << std::string(width, '-') << "+" << std::endl;
        for (int y = 0; y < height; ++y) {
            std::cout << "|" << grid[y] << "|" << std::endl;
        }
        std::cout << "+" << std::string(width, '-') << "+" << std::endl;

        // Print Health Status
        std::cout << "--- STATUS ---" << std::endl;
        for (const Troop* t : troops) {
            std::cout << "  " << t->Card::getCardName() << " HP: " << t->getHealth() << std::endl;
        }
        for (const Building* b : buildings) {
            std::cout << "  " << b->Card::getCardName() << " HP: " << b->getHealth() << std::endl;
        }
        
        // Print Event Log
        std::cout << "--- LOG ---" << std::endl;
        if (eventLog.empty()) {
            std::cout << "  (No actions)" << std::endl;
        }
        for (const std::string& event : eventLog) {
            std::cout << "  > " << event << std::endl;
        }
    }

    // ---AI Helper Methods--- 
    
    // Find nearest alive enemy (from any faction)
    IDamageable* getClosestEnemy(const IDamageable* attacker) const {
        IDamageable* closestTarget = nullptr;
        int minDistance = std::numeric_limits<int>::max();
        Location attackerLoc = attacker->getLocation();

        for (IDamageable* target : allTargets) {
            if (target == attacker || !target->isAlive()) continue;

            int dist = attackerLoc.distanceTo(target->getLocation());
            if (dist < minDistance) {
                minDistance = dist;
                closestTarget = target;
            }
        }
        return closestTarget;
    }

    // Get all alive enemies within radius
    std::vector<IDamageable*> getEnemiesInRadius(Location atLoc, int radius) const {
        std::vector<IDamageable*> targetsInRadius;
        for (IDamageable* target : allTargets) {
            if (target->isAlive() && atLoc.distanceTo(target->getLocation()) <= radius) {
                targetsInRadius.push_back(target);
            }
        }
        return targetsInRadius;
    }
};
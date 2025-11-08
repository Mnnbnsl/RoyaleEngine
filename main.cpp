// main.cpp

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib> // For system()

// --- Our OOP Class Headers ---
#include "Arena.h"
#include "Knight.h"
#include "Archer.h"
#include "Cannon.h"

// --- NEW HELPER FUNCTION ---
/**
 * @brief Clears the console screen.
 * This is OS-dependent. 'cls' is for Windows, 'clear' is for Linux/macOS.
 */
void clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

/**
 * @brief Main function
 */
int main() {
    // --- 1. SETUP PHASE ---
    
    // Clear console one time at the start
    clearConsole();
    std::cout << "========================================" << std::endl;
    std::cout << "  Clash Royale OOP Simulation           " << std::endl;
    std::cout << "========================================" << std::endl;

    Arena arena(20, 10);
    Troop* knight = new Knight();
    //Troop* archer = new Archer();
    Building* cannon = new Cannon();

    knight->deploy(arena, Location(2, 5));
    arena.addTroop(knight); 

    // archer->deploy(arena, Location(17, 5));
    // arena.addTroop(archer);
    
    cannon->deploy(arena, Location(17, 5));
    arena.addBuilding(cannon);

    std::cout << "\n--- INITIAL STATE ---" << std::endl;
    arena.render();
    //std::cout << "A Knight and an Archer face off! Press Enter to start..." << std::endl;
    std::cout << "A Knight charges a Cannon! Press Enter to start..." << std::endl;
    std::cin.get(); 

    // --- 2. SIMULATION LOOP ---
    for (int tick = 1; tick <= 30; ++tick) {
        
        // --- UPDATED ---
        // 1. Clear the screen at the start of the frame
        //clearConsole();
        
        std::cout << "========================================" << std::endl;
        std::cout << "  TICK #" << tick << std::endl;
        std::cout << "========================================" << std::endl;

        // 2. Update the game state (this also builds the log)
        arena.update();
        
        // 3. Render the grid, health, and event log
        arena.render();

        // 4. Check for winner
        if (!knight->isAlive()) {
            std::cout << "\n--- GAME OVER ---" << std::endl;
            std::cout << "The Cannon wins!" << std::endl;
            break; 
        }
        if (!cannon->isAlive()) {
            std::cout << "\n--- GAME OVER ---" << std::endl;
            std::cout << "The Knight wins!" << std::endl;
            break; 
        }

        // 5. Wait 1 second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    // --- 3. CLEANUP PHASE ---
    std::cout << "\n--- SIMULATION END ---" << std::endl;

    if (knight->isAlive() && cannon->isAlive()) {
        std::cout << "Time's up! Both are still standing." << std::endl;
    }

    return 0; 
}
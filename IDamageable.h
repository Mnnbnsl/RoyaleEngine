// Interface for any object that takes damage itself (eg. troop, building, tower)
#pragma once

class IDamageable
{
public:
    // Implementing pure virtual functions
    virtual void takeDamage(int damage) = 0;  // Reduces the object's health by a certain amount
    virtual int getHealth() const = 0;       // getter method to get the current health of object
    virtual bool isAlive() const = 0;       // method to check whether the object is alive or not

    virtual ~IDamageable() {}
};

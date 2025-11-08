// IDamageable.h
#pragma once
#include <string> 

/**
 * @class IDamageable
 * @brief Interface for any object that can take damage.
 */
class IDamageable {
public:
    virtual ~IDamageable() {}

    virtual void takeDamage(int amount) = 0;
    virtual int getHealth() const = 0;
    virtual bool isAlive() const = 0;
    virtual std::string getCardName() const = 0;
    virtual Location getLocation() const = 0;
};
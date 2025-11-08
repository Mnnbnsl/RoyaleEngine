#pragma once
#include <cmath>
#include <string>
#include <sstream>

class Location
{
private:
    int x;
    int y;

public:
    Location(int x = 0, int y = 0) : x(x), y(y) {}

    int getX() const { return x; }
    int getY() const { return y; }

    // Calculates the Manhattan distance ( |x1 - x2| + |y1 - y2| ) between two points.
    int distanceTo(const Location &other) const
    {
        return std::abs(this->x - other.x) + std::abs(this->y - other.y);
    }

    std :: string toString() const
    {
        std :: stringstream ss;
        ss << "(" << x << ", " << y << ")";
        return ss.str();
    }
};
#include "Point.h"

Point::Point(int _x, int _y) : x(_x), y(_y) {
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int _x) {
    x = _x;
}

void Point::setY(int _y) {
    y = _y;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}
#include "Cell.h"

Cell::Cell(char l, const Point& pos) : letter(l), position(pos) {
}

char Cell::getLetter() const {
    return letter;
}

Point Cell::getPosition() const {
    return position;
}

void Cell::setLetter(char l) {
    letter = l;
}

void Cell::setPosition(const Point& pos) {
    position = pos;
}
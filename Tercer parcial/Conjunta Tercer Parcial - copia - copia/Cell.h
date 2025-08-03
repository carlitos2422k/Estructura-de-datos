#ifndef CELL_H
#define CELL_H

#include "Point.h"

class Cell {
private:
    char letter;
    Point position;
    
public:
    Cell(char l = ' ', const Point& pos = Point());
    
    char getLetter() const;
    Point getPosition() const;
    void setLetter(char l);
    void setPosition(const Point& pos);
};

#endif // CELL_H
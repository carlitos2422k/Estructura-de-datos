#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;
    
public:
    Point(int _x = 0, int _y = 0);
    
    int getX() const;
    int getY() const;
    void setX(int _x);
    void setY(int _y);
    
    bool operator==(const Point& other) const;
};

#endif // POINT_H
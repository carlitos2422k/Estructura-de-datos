#ifndef PUNTO_H
#define PUNTO_H

class Punto {
private:
    int x;
    int y;
    
public:
    Punto(int _x = 0, int _y = 0);
    
    int obtenerX() const;
    int obtenerY() const;
    void establecerX(int _x);
    void establecerY(int _y);
    
    bool operator==(const Punto& otro) const;
};

#endif // PUNTO_H
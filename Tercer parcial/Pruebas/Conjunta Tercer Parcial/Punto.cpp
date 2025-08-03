#include "Punto.h"

Punto::Punto(int _x, int _y) : x(_x), y(_y) {
}

int Punto::obtenerX() const {
    return x;
}

int Punto::obtenerY() const {
    return y;
}

void Punto::establecerX(int _x) {
    x = _x;
}

void Punto::establecerY(int _y) {
    y = _y;
}

bool Punto::operator==(const Punto& otro) const {
    return x == otro.x && y == otro.y;
}
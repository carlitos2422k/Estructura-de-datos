#include "Celda.h"

Celda::Celda(char l, const Punto& pos) : letra(l), posicion(pos) {
}

char Celda::obtenerLetra() const {
    return letra;
}

Punto Celda::obtenerPosicion() const {
    return posicion;
}

void Celda::establecerLetra(char l) {
    letra = l;
}

void Celda::establecerPosicion(const Punto& pos) {
    posicion = pos;
}
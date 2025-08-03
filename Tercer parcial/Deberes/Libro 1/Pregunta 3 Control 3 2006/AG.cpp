#include "AG.h"
#include <iostream>

// Constructor de la clase AG
AG::AG(std::string nombre) {
    this->nombrePersona = nombre;
    this->padrePersona = nullptr;
    this->madrePersona = nullptr;
}

// Retorna el nombre de la persona
std::string AG::nombre() {
    return nombrePersona;
}

// Registra el padre y madre de una persona
void AG::agregar(std::string hijo, std::string padre, std::string madre) {
    if (nombrePersona == hijo) {
        this->padrePersona = new AG(padre);
        this->madrePersona = new AG(madre);
    }
}

// Obtiene el nombre del padre de una persona
std::string AG::padre(std::string hijo) {
    if (nombrePersona == hijo && padrePersona != nullptr) {
        return padrePersona->nombre();
    }
    return "null";
}

// Obtiene el nombre de la madre de una persona
std::string AG::madre(std::string hijo) {
    if (nombrePersona == hijo && madrePersona != nullptr) {
        return madrePersona->nombre();
    }
    return "null";
}

// Método para determinar si dos personas son primos
bool AG::primos(AG* x, AG* y) {
    // Verificamos si los padres de x e y son hermanos
    std::string padreX = x->padre(x->nombre());
    std::string madreX = x->madre(x->nombre());
    std::string padreY = y->padre(y->nombre());
    std::string madreY = y->madre(y->nombre());

    // Si alguno de los padres de X es igual a alguno de los padres de Y, son primos
    return (padreX == padreY) || (padreX == madreY) || (madreX == padreY) || (madreX == madreY);
}

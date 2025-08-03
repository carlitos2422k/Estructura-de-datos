#ifndef TORNEO_H
#define TORNEO_H

#include <string>
#include <vector>
#include "Nodo.h"

class Torneo {
private:
    Nodo* raiz;

    int lugarRecursivo(std::string x, int n, Nodo* r);
    void lugaresRecursivo(int n, Nodo* r, std::vector<std::string>& jugadores);

public:
    Torneo();
    void resultado(std::string x, std::string y);
    int lugar(std::string x);
    std::string jugador(int x);
    void lugares(Torneo t);
};

#endif

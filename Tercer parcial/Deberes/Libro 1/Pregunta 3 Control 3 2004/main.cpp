#include <iostream>
#include "Torneo.h"

int main() {
    Torneo torneo;
    
    // Aquí agregar los resultados del torneo
    torneo.resultado("Jugador1", "Jugador2");
    torneo.resultado("Jugador3", "Jugador4");

    // Mostrar la clasificación completa
    torneo.lugares(torneo);

    return 0;
}

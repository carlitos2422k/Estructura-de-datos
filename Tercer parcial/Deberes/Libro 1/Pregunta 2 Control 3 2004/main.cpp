#include <iostream>
#include "Olimpiada.h"

int main() {
    Olimpiada olimpiada;

    // Registrar resultados de competencias
    olimpiada.competencia("tenis masc", "Chile", "Chile", "España");
    olimpiada.competencia("futbol", "Brasil", "Chile", "España");

    // Mostrar los resultados de las olimpiadas
    olimpiada.mostrarResultados();

    // Consultar medallas
    std::cout << "Medallas de oro de Chile: " << olimpiada.oros("Chile") << std::endl;
    std::cout << "Medallas de plata de Chile: " << olimpiada.platas("Chile") << std::endl;
    std::cout << "Medallas de bronce de Chile: " << olimpiada.bronces("Chile") << std::endl;
    std::cout << "Lugar de Chile: " << olimpiada.lugar("Chile") << std::endl;

    // Mostrar el país en el lugar 2
    std::cout << "País en el lugar 2: " << olimpiada.pais(2) << std::endl;

    return 0;
}

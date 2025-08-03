#include <iostream>
#include "AG.h"

int main() {
    // Crear personas
    AG a("A");
    AG b("B");
    AG c("C");
    AG d("D");

    // Agregar padres
    a.agregar("A", "B", "C");
    b.agregar("B", "E", "F");
    c.agregar("C", "G", "H");
    d.agregar("D", "B", "C");

    // Imprimir nombre de la persona
    std::cout << "Nombre de A: " << a.nombre() << std::endl;
    
    // Verificar si A y D son primos
    bool sonPrimos = AG::primos(&a, &d);
    std::cout << "A y D son primos? " << (sonPrimos ? "Sí" : "No") << std::endl;
    
    return 0;
}

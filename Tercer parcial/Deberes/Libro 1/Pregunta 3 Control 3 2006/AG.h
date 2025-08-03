#ifndef AG_H
#define AG_H

#include <string>
#include <unordered_map>

class AG {
private:
    std::string nombrePersona;
    AG* padrePersona;
    AG* madrePersona;

public:
    // Constructor
    AG(std::string nombre);

    // Métodos para obtener el nombre, agregar padres, y obtener el padre o madre de una persona
    std::string nombre();
    void agregar(std::string hijo, std::string padre, std::string madre);
    std::string padre(std::string hijo);
    std::string madre(std::string hijo);

    // Método para verificar si dos personas son primos
    static bool primos(AG* x, AG* y);
};

#endif

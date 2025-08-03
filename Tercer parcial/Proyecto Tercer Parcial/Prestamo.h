#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <string>
#include <iostream>
#include <ctime>

class Prestamo {
private:
    std::string id_prestamo;
    std::string id_usuario;
    std::string id_libro;
    std::string fecha_prestamo;
    std::string fecha_devolucion;
    std::string estado;

public:
    Prestamo(std::string id_prestamo, std::string id_usuario, std::string id_libro, 
             std::string fecha_prestamo, std::string fecha_devolucion, std::string estado);
    bool fueDevueltoATiempo() const;
    bool estaVencido() const;
    std::string getIdPrestamo() const;
    std::string getIdUsuario() const;
    std::string getIdLibro() const;
    std::string getFechaPrestamo() const;
    std::string getFechaDevolucion() const;
    std::string getEstado() const;

    void setEstado(std::string estado);
};

// Nodo para la lista doble circular
class Nodo {
public:
    Prestamo prestamo;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const Prestamo& prestamo);
};

// Lista doble circular
class ListaDobleCircular {
private:
    Nodo* cabeza;

public:
    ListaDobleCircular();
    ~ListaDobleCircular();

    void insertar(const Prestamo& prestamo);
    void eliminar(std::string id_prestamo);
    void mostrarHistorial() const;
    bool estaVacia() const;
    Nodo* getCabeza() const { return cabeza; }
};

#endif
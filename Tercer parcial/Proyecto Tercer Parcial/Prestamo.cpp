#include "Prestamo.h"

// Implementación de la clase Prestamo
Prestamo::Prestamo(std::string id_prestamo, std::string id_usuario, std::string id_libro, 
                   std::string fecha_prestamo, std::string fecha_devolucion, std::string estado)
    : id_prestamo(id_prestamo), id_usuario(id_usuario), id_libro(id_libro), 
      fecha_prestamo(fecha_prestamo), fecha_devolucion(fecha_devolucion), estado(estado) {}

bool Prestamo::fueDevueltoATiempo() const {
    if (estado != "Devuelto") {
        return false;
    }
    
    // Convertir fechas a formato de tiempo
    struct std::tm tmFechaDevolucion = {};
    struct std::tm tmFechaActual = {};
    
    std::sscanf(fecha_devolucion.c_str(), "%d-%d-%d", 
                &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
    tmFechaDevolucion.tm_year -= 1900;
    tmFechaDevolucion.tm_mon -= 1;
    
    std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
    std::time_t fechaActualT = std::time(nullptr);
    
    return fechaActualT <= fechaDevolucionT;
}

bool Prestamo::estaVencido() const {
    if (estado != "Activo") {
        return false;
    }
    
    // Convertir fechas a formato de tiempo
    struct std::tm tmFechaDevolucion = {};
    
    std::sscanf(fecha_devolucion.c_str(), "%d-%d-%d", 
                &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
    tmFechaDevolucion.tm_year -= 1900;
    tmFechaDevolucion.tm_mon -= 1;
    
    std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
    std::time_t fechaActualT = std::time(nullptr);
    
    return fechaActualT > fechaDevolucionT;
}

std::string Prestamo::getIdPrestamo() const { return id_prestamo; }
std::string Prestamo::getIdUsuario() const { return id_usuario; }
std::string Prestamo::getIdLibro() const { return id_libro; }
std::string Prestamo::getFechaPrestamo() const { return fecha_prestamo; }
std::string Prestamo::getFechaDevolucion() const { return fecha_devolucion; }
std::string Prestamo::getEstado() const { return estado; }

void Prestamo::setEstado(std::string estado) { this->estado = estado; }

// Implementación de la clase Nodo
Nodo::Nodo(const Prestamo& prestamo) : prestamo(prestamo), siguiente(nullptr), anterior(nullptr) {}

// Implementación de la clase ListaDobleCircular
ListaDobleCircular::ListaDobleCircular() : cabeza(nullptr) {}

ListaDobleCircular::~ListaDobleCircular() {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    } while (actual != cabeza);
}

bool ListaDobleCircular::estaVacia() const {
    return cabeza == nullptr;
}

void ListaDobleCircular::insertar(const Prestamo& prestamo) {
    Nodo* nuevo = new Nodo(prestamo);

    if (!cabeza) {
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        Nodo* ultimo = cabeza->anterior;
        ultimo->siguiente = nuevo;
        nuevo->anterior = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->anterior = nuevo;
    }
}

void ListaDobleCircular::eliminar(std::string id_prestamo) {
    if (!cabeza) return;

    Nodo* actual = cabeza;
    do {
        if (actual->prestamo.getIdPrestamo() == id_prestamo) {
            if (actual == cabeza && actual->siguiente == cabeza) {
                delete actual;
                cabeza = nullptr;
                return;
            }

            Nodo* anterior = actual->anterior;
            Nodo* siguiente = actual->siguiente;

            anterior->siguiente = siguiente;
            siguiente->anterior = anterior;

            if (actual == cabeza) cabeza = siguiente;

            delete actual;
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
}

void ListaDobleCircular::mostrarHistorial() const {
    if (!cabeza) {
        std::cout << "No hay préstamos en el historial." << std::endl;
        return;
    }

    Nodo* actual = cabeza;
    do {
        std::cout << "ID Prestamo: " << actual->prestamo.getIdPrestamo()
                  << " | ID Usuario: " << actual->prestamo.getIdUsuario()
                  << " | ID Libro: " << actual->prestamo.getIdLibro()
                  << " | Estado: " << actual->prestamo.getEstado()
                  << std::endl;
        actual = actual->siguiente;
    } while (actual != cabeza);
}
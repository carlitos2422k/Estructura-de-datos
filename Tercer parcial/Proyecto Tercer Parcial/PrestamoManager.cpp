#include "PrestamoManager.h"
#include <cmath>


std::string PrestamoManager::generarIdPrestamo() {
    // Verificar si el contador alcanzó el máximo
    if (contadorIdPrestamo >= 9999) {
        std::cerr << "Advertencia: Se alcanzo el limite de IDs. Reiniciando contador." << std::endl;
        contadorIdPrestamo = 0;
    }
    
    contadorIdPrestamo++;
    std::stringstream ss;
    ss << "P" << std::setw(4) << std::setfill('0') << contadorIdPrestamo;
    return ss.str();
}

std::string PrestamoManager::obtenerFechaActual() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    
    std::stringstream ss;
    ss << (now->tm_year + 1900) << "-" 
       << std::setw(2) << std::setfill('0') << (now->tm_mon + 1) << "-" 
       << std::setw(2) << std::setfill('0') << now->tm_mday;
    
    return ss.str();
}

std::string PrestamoManager::calcularFechaDevolucion(int diasPrestamo) {
    std::time_t t = std::time(nullptr);
    t += diasPrestamo * 24 * 60 * 60; // Convertir días a segundos
    std::tm* future = std::localtime(&t);
    
    std::stringstream ss;
    ss << (future->tm_year + 1900) << "-" 
       << std::setw(2) << std::setfill('0') << (future->tm_mon + 1) << "-" 
       << std::setw(2) << std::setfill('0') << future->tm_mday;
    
    return ss.str();
}

bool PrestamoManager::solicitarPrestamo(Usuario* usuario, const std::string& codigoLibro, int diasPrestamo) {
    // Verificar que el usuario no sea nullptr
    if (!usuario) {
        std::cout << "Error: Usuario no valido." << std::endl;
        return false;
    }
    
    // Buscar el libro en el árbol AVL
    Libro* libro = arbolLibros->buscar(codigoLibro);
    
    // Verificar que el libro exista
    if (!libro) {
        std::cout << "Error: El libro con codigo " << codigoLibro << " no existe." << std::endl;
        return false;
    }
    
    // Verificar que haya copias disponibles
    if (libro->getCopiasDisponibles() <= 0) {
        std::cout << "Error: No hay copias disponibles del libro \"" << libro->getTitulo() << "\"." << std::endl;
        return false;
    }
    
    // Usar días de préstamo predeterminados si no se especifica
    if (diasPrestamo <= 0) {
        diasPrestamo = diasPrestamoPredeterminado;
    }
    
    // Generar ID de préstamo único
    std::string idPrestamo = generarIdPrestamo();
    
    // Obtener fechas
    std::string fechaPrestamo = obtenerFechaActual();
    std::string fechaDevolucion = calcularFechaDevolucion(diasPrestamo);
    
    // Crear el préstamo
    Prestamo nuevoPrestamo(
        idPrestamo,
        usuario->getIdUsuario(),
        codigoLibro,
        fechaPrestamo,
        fechaDevolucion,
        "Activo"
    );
    
    // Añadir al historial de préstamos
    historialPrestamos->insertar(nuevoPrestamo);
    
    // Actualizar el número de copias disponibles
    libro->setCopiasDisponibles(libro->getCopiasDisponibles() - 1);
    
    std::cout << "Prestamo registrado con exito:\n"
              << "ID Prestamo: " << idPrestamo << "\n"
              << "Libro: " << libro->getTitulo() << "\n"
              << "Fecha prestamo: " << fechaPrestamo << "\n"
              << "Fecha devolucion: " << fechaDevolucion << "\n";
    
    return true;
}

bool PrestamoManager::devolverLibro(const std::string& idPrestamo) {
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        std::cout << "Error: No hay prestamos registrados." << std::endl;
        return false;
    }
    
    // Buscar el préstamo en la lista circular
    Nodo* actual = historialPrestamos->getCabeza();
    Prestamo* prestamoEncontrado = nullptr;
    std::string idLibro;
    
    do {
        if (actual->prestamo.getIdPrestamo() == idPrestamo) {
            prestamoEncontrado = &(actual->prestamo);
            idLibro = prestamoEncontrado->getIdLibro();
            break;
        }
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    if (!prestamoEncontrado) {
        std::cout << "Error: Prestamo no encontrado." << std::endl;
        return false;
    }
    
    // Verificar que el préstamo esté activo
    if (prestamoEncontrado->getEstado() != "Activo") {
        std::cout << "Error: El prestamo ya fue devuelto o cancelado." << std::endl;
        return false;
    }
    
    // Buscar el libro en el árbol AVL
    Libro* libro = arbolLibros->buscar(idLibro);
    if (!libro) {
        std::cout << "Error: El libro asociado al prestamo no existe." << std::endl;
        return false;
    }
    
    // Incrementar el contador de copias disponibles
    libro->setCopiasDisponibles(libro->getCopiasDisponibles() + 1);
    
    // Cambiar el estado del préstamo a "Devuelto"
    prestamoEncontrado->setEstado("Devuelto");
    
    std::cout << "Libro \"" << libro->getTitulo() << "\" devuelto correctamente." << std::endl;
    
    return true;
}

std::vector<Prestamo> PrestamoManager::buscarPrestamosUsuario(const std::string& idUsuario) {
    std::vector<Prestamo> prestamosUsuario;
    
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        return prestamosUsuario;
    }
    
    Nodo* actual = historialPrestamos->getCabeza();
    
    do {
        if (actual->prestamo.getIdUsuario() == idUsuario && 
            actual->prestamo.getEstado() == "Activo") {
            prestamosUsuario.push_back(actual->prestamo);
        }
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    return prestamosUsuario;
}

void PrestamoManager::setDiasPrestamoPredeterminado(int dias) {
    if (dias > 0) {
        diasPrestamoPredeterminado = dias;
    }
}

int PrestamoManager::getDiasPrestamoPredeterminado() const {
    return diasPrestamoPredeterminado;
}


PrestamoManager::PrestamoManager(ArbolAVL* arbolLibros, ListaDobleCircular* historialPrestamos) 
    : arbolLibros(arbolLibros), historialPrestamos(historialPrestamos), 
      diasPrestamoPredeterminado(14), contadorIdPrestamo(0), multaPorDia(5.0) {}

std::vector<Prestamo> PrestamoManager::obtenerHistorialPrestamoUsuario(const std::string& idUsuario) {
    std::vector<Prestamo> historialUsuario;
    
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        return historialUsuario;
    }
    
    Nodo* actual = historialPrestamos->getCabeza();
    
    do {
        if (actual->prestamo.getIdUsuario() == idUsuario) {
            historialUsuario.push_back(actual->prestamo);
        }
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    return historialUsuario;
}

std::vector<Prestamo> PrestamoManager::obtenerTodosLosPrestamos() const {
    std::vector<Prestamo> todosPrestamos;
    
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        return todosPrestamos;
    }
    
    Nodo* actual = historialPrestamos->getCabeza();
    
    do {
        todosPrestamos.push_back(actual->prestamo);
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    return todosPrestamos;
}

std::vector<Prestamo> PrestamoManager::obtenerPrestamosVencidos() const {
    std::vector<Prestamo> prestamosVencidos;
    
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        return prestamosVencidos;
    }
    
    Nodo* actual = historialPrestamos->getCabeza();
    
    do {
        if (actual->prestamo.getEstado() == "Activo" && actual->prestamo.estaVencido()) {
            prestamosVencidos.push_back(actual->prestamo);
        }
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    return prestamosVencidos;
}

bool PrestamoManager::cambiarEstadoPrestamo(const std::string& idPrestamo, const std::string& nuevoEstado) {
    if (!historialPrestamos || historialPrestamos->estaVacia()) {
        return false;
    }
    
    Nodo* actual = historialPrestamos->getCabeza();
    
    do {
        if (actual->prestamo.getIdPrestamo() == idPrestamo) {
            actual->prestamo.setEstado(nuevoEstado);
            return true;
        }
        actual = actual->siguiente;
    } while (actual != historialPrestamos->getCabeza());
    
    return false;
}

int PrestamoManager::calcularMulta(const Prestamo& prestamo) const {
    if (prestamo.getEstado() != "Activo" || !prestamo.estaVencido()) {
        return 0;
    }
    
    // Convertir fechas a formato de tiempo
    struct std::tm tmFechaDevolucion = {};
    
    std::sscanf(prestamo.getFechaDevolucion().c_str(), "%d-%d-%d", 
                &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
    tmFechaDevolucion.tm_year -= 1900;
    tmFechaDevolucion.tm_mon -= 1;
    
    std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
    std::time_t fechaActualT = std::time(nullptr);
    
    // Calcular días de retraso
    double diasRetraso = std::difftime(fechaActualT, fechaDevolucionT) / (60 * 60 * 24);
    
    return static_cast<int>(std::ceil(diasRetraso) * multaPorDia);
}

void PrestamoManager::setMultaPorDia(double monto) {
    if (monto > 0) {
        multaPorDia = monto;
    }
}

double PrestamoManager::getMultaPorDia() const {
    return multaPorDia;
}

void PrestamoManager::setContadorIdPrestamo(int contador) {
    if (contador >= 0) {
        contadorIdPrestamo = contador;
    }
}

int PrestamoManager::getContadorIdPrestamo() const {
    return contadorIdPrestamo;
}
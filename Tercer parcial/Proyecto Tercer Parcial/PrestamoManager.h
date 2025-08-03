#ifndef PRESTAMO_MANAGER_H
#define PRESTAMO_MANAGER_H

#include "ArbolAVL.h"
#include "Prestamo.h"
#include "Usuario.h"
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>

class PrestamoManager {
private:
    ArbolAVL* arbolLibros;
    ListaDobleCircular* historialPrestamos;
    int diasPrestamoPredeterminado;
    int contadorIdPrestamo;

    // Genera un nuevo ID de préstamo único
    std::string generarIdPrestamo();
    
    // Obtiene la fecha actual en formato YYYY-MM-DD
    std::string obtenerFechaActual();
    
    // Calcula la fecha de devolución basada en la fecha actual y los días de préstamo
    std::string calcularFechaDevolucion(int diasPrestamo);
    double multaPorDia;
public:
    PrestamoManager(ArbolAVL* arbolLibros, ListaDobleCircular* historialPrestamos);
    std::vector<Prestamo> obtenerHistorialPrestamoUsuario(const std::string& idUsuario);
    std::vector<Prestamo> obtenerTodosLosPrestamos() const;
    std::vector<Prestamo> obtenerPrestamosVencidos() const;
    bool cambiarEstadoPrestamo(const std::string& idPrestamo, const std::string& nuevoEstado);
    int calcularMulta(const Prestamo& prestamo) const;
    void setMultaPorDia(double monto);
    double getMultaPorDia() const;
    // Solicitar un préstamo
    bool solicitarPrestamo(Usuario* usuario, const std::string& codigoLibro, int diasPrestamo = 0);
    
    // Devolver un libro
    bool devolverLibro(const std::string& idPrestamo);
    
    // Buscar préstamos activos de un usuario
    std::vector<Prestamo> buscarPrestamosUsuario(const std::string& idUsuario);
    
    // Establecer la duración predeterminada de préstamo en días
    void setDiasPrestamoPredeterminado(int dias);
    
    // Obtener la duración predeterminada de préstamo en días
    int getDiasPrestamoPredeterminado() const;
    
    // Establecer el contador de ID de préstamo (para persistencia)
    void setContadorIdPrestamo(int contador);
    
    // Obtener el contador actual de ID de préstamo
    int getContadorIdPrestamo() const;
};

#endif
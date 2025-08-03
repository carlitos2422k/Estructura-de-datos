#ifndef RECOMENDACION_MANAGER_H
#define RECOMENDACION_MANAGER_H

#include "PrestamoManager.h"
#include "ArbolAVL.h"
#include "HashUsuario.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <chrono>  // Añadir para medición de tiempo
#include <iomanip>

// Estructura para representar una recomendación con su puntuación
struct Recomendacion {
    Libro* libro;
    double puntuacion;
    std::vector<std::string> razones;

    // Constructor con parámetros
    Recomendacion(Libro* libro, double puntuacion) : libro(libro), puntuacion(puntuacion) {}
    
    // Constructor predeterminado (necesario para resize)
    Recomendacion() : libro(nullptr), puntuacion(0.0) {}

    // Operador de comparación para ordenar recomendaciones por puntuación (mayor a menor)
    bool operator<(const Recomendacion& other) const {
        return puntuacion > other.puntuacion; // Orden descendente
    }
};

class RecomendacionManager {
private:
    PrestamoManager* prestamoManager;
    ArbolAVL* arbolLibros;
    HashUsuario* hashUsuarios;

    // Mapeo de usuarios a géneros prestados (con frecuencia)
    std::unordered_map<std::string, std::map<std::string, int>> perfilesUsuarios;
    
    // Mapeo de géneros a otros géneros relacionados con pesos
    std::unordered_map<std::string, std::map<std::string, double>> relacionGeneros;
    
    // Mapeo de libros a su frecuencia de préstamo
    std::map<std::string, int> popularidadLibros;
    
    // Parámetros para el algoritmo de recomendación
    double pesoHistorialPersonal;     // Importancia del historial del usuario
    double pesoPopularidad;           // Importancia de la popularidad general
    double pesoRelacionGeneros;       // Importancia de géneros relacionados
    double pesoNovedades;             // Importancia de libros recientes
    int maxRecomendaciones;           // Número máximo de recomendaciones a generar
    
    // Métodos auxiliares
    void analizarHistorialPrestamos();
    void calcularRelacionesGeneros();
    void calcularPopularidadLibros();
    
    // Método de backtracking para generar recomendaciones
    void backtrackRecomendaciones(
        const std::string& idUsuario,
        std::vector<Recomendacion>& recomendacionesActuales,
        std::vector<Recomendacion>& mejoresRecomendaciones,
        std::set<std::string>& librosConsiderados,
        std::vector<Libro*>& candidatos,
        int nivel,
        double puntuacionActual,
        double& mejorPuntuacion);

    // Calcular puntuación de un libro para un usuario específico
    double calcularPuntuacionLibro(const std::string& idUsuario, Libro* libro, std::vector<std::string>& razones);
    
    // Verificar si un libro ya ha sido prestado por un usuario
    bool libroYaPrestado(const std::string& idUsuario, const std::string& codigoLibro);

public:
    RecomendacionManager(PrestamoManager* prestamoManager, ArbolAVL* arbolLibros, HashUsuario* hashUsuarios);
    
    // Inicializar los perfiles y relaciones
    void inicializar();
    
    // Configurar parámetros del algoritmo de recomendación
    void configurarParametros(double pesoHistorial, double pesoPopularidad, 
                            double pesoRelacion, double pesoNovedades, int maxRecom);
    
    // Generar recomendaciones para un usuario específico
    std::vector<Recomendacion> generarRecomendaciones(const std::string& idUsuario, int cantidad = 5);
    
    // Método de depuración para mostrar el perfil de un usuario
    void mostrarPerfilUsuario(const std::string& idUsuario);
    double getPesoHistorialPersonal() const { return pesoHistorialPersonal; }
    double getPesoPopularidad() const { return pesoPopularidad; }
    double getPesoRelacionGeneros() const { return pesoRelacionGeneros; }
    double getPesoNovedades() const { return pesoNovedades; }
    int getMaxRecomendaciones() const { return maxRecomendaciones; }
};

#endif
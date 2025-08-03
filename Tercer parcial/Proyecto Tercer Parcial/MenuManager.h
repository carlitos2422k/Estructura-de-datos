#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "HashUsuario.h"
#include "ArbolAVL.h"
#include "PrestamoManager.h"
#include "DatabaseManager.h"
#include "RecomendacionManager.h" // Incluir el nuevo gestor de recomendaciones
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>  // Para _getch() en Windows
#include <windows.h> // Para mover el cursor
#include <thread>  // Para std::this_thread::sleep_for
#include <chrono>  // Para std::chrono::seconds
#include <vector>
#include "Validacion.h"
class MenuManager {
private:


    HashUsuario* hashUsuarios;
    ArbolAVL* arbolLibros;
    PrestamoManager* prestamoManager;
    DatabaseManager* dbManager;
    RecomendacionManager* recomendacionManager; // Añadir el nuevo gestor

    // Utilidades
    void limpiarPantalla();
    void pausa();

    //Utilidades para tablas dinámicas
    void imprimirLineaHorizontal(const std::vector<int>& anchos) const;
    void imprimirFilaTabla(const std::vector<std::string>& datos, const std::vector<int>& anchos) const;
    std::vector<int> calcularAnchosColumnas(const std::vector<std::vector<std::string>>& datos, const std::vector<std::string>& encabezados) const;

    // Funciones de menú generales
    void modificarPerfilUsuario(Usuario* usuario);
    void gestionarUsuarios();
    void gestionarLibros();
    bool iniciarSesion();
    bool registrarUsuario(bool esAdmin = false);

    // Funciones de menú de préstamos (integradas de MenuPrestamos)
    void mostrarLibrosDisponibles();
    void mostrarHistorialPrestamos(Usuario* usuario);
    void mostrarPrestamosVencidos();
    void verMultasUsuario(Usuario* usuario);
    void solicitarPrestamo(Usuario* usuario);
    void devolverLibro(Usuario* usuario);
    void mostrarPrestamosActivos(Usuario* usuario);
    void mostrarHistorialUsuarioParaAdmin(const std::string& idUsuario);
    void generarReporteGeneral();
    void mostrarTodosLosPrestamos();
    
    // Nueva función para recomendaciones
    void mostrarRecomendacionesPersonalizadas(Usuario* usuario);
    void configurarRecomendador();
    void abrirAyudaHTML();

public:
    MenuManager(HashUsuario* hashUsuarios, ArbolAVL* arbolLibros, 
                PrestamoManager* prestamoManager, DatabaseManager* dbManager = nullptr);
    ~MenuManager(); // Destructor para liberar la memoria del recomendador
    
    void cargarLibrosEjemplo();
    void ejecutarMenuPrincipal();
    
    // Getter para PrestamoManager (útil si se necesita acceso desde el exterior)
    PrestamoManager* getPrestamoManager() const {
        return prestamoManager;
    }
    
    // Establecer el gestor de base de datos
    void setDatabaseManager(DatabaseManager* dbManager);
    
    // Inicializar el sistema de recomendaciones
    void inicializarRecomendador();
    //Menu dinamico

    void gotoxy(int x, int y);
    int mostrarMenuDinamico(const std::string& titulo, const std::vector<std::string>& opciones, int posX = 0, int posY = 0);
    bool mostrarMenuConfirmacion(const std::string& titulo);
    std::string mostrarMenuBackups(const std::vector<std::string>& backups);
    
};

#endif
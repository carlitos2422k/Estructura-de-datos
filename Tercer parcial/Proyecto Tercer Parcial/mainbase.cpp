#include <iostream>
#include "HashUsuario.h"
#include "Usuario.h"
#include "Libro.h" 
#include "ArbolAVL.h"
#include "PrestamoManager.h"
#include "MenuManager.h"
#include "DatabaseManager.h"

int main() {
    // Crear la tabla hash para usuarios
    HashUsuario hashUsuarios;
    hashUsuarios.setProbingMethod(true); // Usar Quadratic Probing
    
    // Crear árbol AVL para libros
    ArbolAVL arbolLibros;
    
    // Crear lista doble circular para el historial de préstamos
    ListaDobleCircular historialPrestamos;
    PrestamoManager prestamoManager(&arbolLibros, &historialPrestamos);
    
    // Crear DatabaseManager para persistencia
    DatabaseManager dbManager(&arbolLibros, &hashUsuarios, &historialPrestamos, &prestamoManager);
    
    // Crear gestor de menús unificado
    MenuManager menuManager(&hashUsuarios, &arbolLibros, &prestamoManager, &dbManager);
    
    // Menú de carga de backups
    std::vector<std::string> opcionesBackup = {"Si", "No"};
    int seleccionBackup = menuManager.mostrarMenuDinamico("¿Desea cargar un backup?", opcionesBackup);
    
    if (seleccionBackup == 0) {
        std::vector<std::string> backups = dbManager.obtenerListaBackups();
        
        if (backups.empty()) {
            std::cout << "No hay backups disponibles. Se cargaran los datos actuales." << std::endl;
            dbManager.cargarTodo();
        } else {
            std::string rutaSeleccionada = menuManager.mostrarMenuBackups(backups);
            
            if (rutaSeleccionada.empty()) {
                std::cout << "Se cargaran los datos actuales." << std::endl;
                dbManager.cargarTodo();
            } else {
                // Cargar primero los usuarios y libros normalmente
                dbManager.cargarLibros();
                dbManager.cargarUsuarios();

                // Luego cargar los préstamos del backup seleccionado
                std::cout << "Cargando backup: " << dbManager.formatearNombreBackup(rutaSeleccionada) << std::endl;
                bool resultado = dbManager.cargarBackupEspecifico(rutaSeleccionada);
                if(resultado){
                    std::cout << "Backup cargado exitosamente." << std::endl;
                }else{
                    std::cout << "No se pudo cargar el backup. Se usaran los datos actuales de prestamos." << std::endl;
                    dbManager.cargarPrestamos();
                }
            }
        }
    } else {
        // Cargar datos guardados normalmente
        dbManager.cargarTodo();
    }
    
    // Inicializar datos de ejemplo solo si no se han cargado datos
    if (arbolLibros.estaVacio()) {
        std::cout << "No se encontraron libros. Cargando datos de ejemplo..." << std::endl;
        menuManager.cargarLibrosEjemplo();
        
        // Crear usuarios y administradores de ejemplo para facilitar pruebas
        hashUsuarios.insert(new Usuario("U001", "Juan Perez", "juan@email.com", "user123"));
        hashUsuarios.insert(new Administrador("A001", "Admin Principal", "admin@biblioteca.com", "admin123"));
    }
    
    std::cout << "¡Bienvenido al Sistema de Gestión de Biblioteca!\n";
    std::cout << "Para probar, puede usar las siguientes credenciales:\n";
    std::cout << "- Usuario regular: ID: U001, Contraseña: user123\n";
    std::cout << "- Administrador: ID: A001, Contraseña: admin123\n";
    
    // Ejecutar el menú principal
    menuManager.ejecutarMenuPrincipal();
    
    // Guardar datos antes de salir
    std::cout << "Guardando datos..." << std::endl;
    dbManager.guardarTodo();
    
    return 0;
}
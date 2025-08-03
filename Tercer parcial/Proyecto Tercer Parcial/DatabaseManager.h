#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include "ArbolAVL.h"
#include "HashUsuario.h"
#include "Libro.h"
#include "Usuario.h"
#include "Prestamo.h"
#include "PrestamoManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class DatabaseManager {
private:
    const std::string LIBROS_FILE = "libros.txt";
    const std::string USUARIOS_FILE = "usuarios.txt";
    const std::string PRESTAMOS_FILE = "prestamos.txt";
    const std::string BACKUP_PATH = "C:\\Users\\Carlos\\Desktop\\Estructura de datos\\Tercer parcial\\Proyecto Tercer Parcial\\backups\\";
    ArbolAVL* arbolLibros;
    HashUsuario* hashUsuarios;
    ListaDobleCircular* historialPrestamos;
    PrestamoManager* prestamoManager;

    //backups
    std::string obtenerNombreBackupDiario();
    bool esArchivoBackup(const std::string& nombreArchivo);
    
public:
    DatabaseManager(ArbolAVL* arbolLibros, HashUsuario* hashUsuarios, 
                   ListaDobleCircular* historialPrestamos, PrestamoManager* prestamoManager);
    
    // Métodos para libros
    bool guardarLibros();
    bool cargarLibros();
    
    // Métodos para usuarios
    bool guardarUsuarios();
    bool cargarUsuarios();
    
    // Métodos para préstamos
    bool guardarPrestamos();
    bool cargarPrestamos();
    
    // Método para guardar todos los datos
    bool guardarTodo();
    
    // Método para cargar todos los datos
    bool cargarTodo();

    //backups
    bool guardarBackupDiario();
    bool cargarBackupEspecifico(const std::string& nombreArchivo);
    std::vector<std::string> obtenerListaBackups();
    std::string formatearNombreBackup(const std::string& nombreArchivo);
};

#endif
#include "DatabaseManager.h"
#include <chrono>
#include <iomanip>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#endif

DatabaseManager::DatabaseManager(ArbolAVL* arbolLibros, HashUsuario* hashUsuarios, 
    ListaDobleCircular* historialPrestamos, PrestamoManager* prestamoManager)
: arbolLibros(arbolLibros), hashUsuarios(hashUsuarios), 
historialPrestamos(historialPrestamos), prestamoManager(prestamoManager) {

// Validar que los punteros no sean nulos
if (!arbolLibros || !hashUsuarios || !historialPrestamos || !prestamoManager) {
std::cerr << "Error: Se ha proporcionado un puntero nulo al constructor de DatabaseManager." << std::endl;
// Se podría lanzar una excepción aquí, pero por simplicidad solo se muestra un error
}
}
// Métodos para libros
bool DatabaseManager::guardarLibros() {
    std::ofstream file(LIBROS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << LIBROS_FILE << " para escritura." << std::endl;
        return false;
    }
    
    std::vector<Libro*> libros = arbolLibros->inOrden();
    
    for (Libro* libro : libros) {
        file << libro->getTitulo() << ";"
             << libro->getAutor() << ";"
             << libro->getCodigo() << ";"
             << libro->getUbicacion() << ";"
             << libro->getGenero() << ";"
             << libro->getCopiasDisponibles() << std::endl;
    }
    
    file.close();
    std::cout << "Libros guardados correctamente en " << LIBROS_FILE << std::endl;
    return true;
}

// En DatabaseManager.cpp, en el método cargarLibros()
bool DatabaseManager::cargarLibros() {
    std::ifstream file(LIBROS_FILE);
    if (!file.is_open()) {
        std::cerr << "Advertencia: No se pudo abrir el archivo " << LIBROS_FILE << " para lectura." << std::endl;
        return false;
    }
    
    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string titulo, autor, codigo, ubicacion, genero, copiasStr;
        
        std::getline(ss, titulo, ';');
        std::getline(ss, autor, ';');
        std::getline(ss, codigo, ';');
        std::getline(ss, ubicacion, ';');
        std::getline(ss, genero, ';');
        std::getline(ss, copiasStr, ';');
        
        int copias = 0; // Valor por defecto
        try {
            copias = std::stoi(copiasStr);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error al convertir el número de copias para el libro " << titulo 
                      << ": " << e.what() << ". Se usara 0 como valor predeterminado." << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Numero de copias fuera de rango para el libro " << titulo 
                      << ": " << e.what() << ". Se usara 0 como valor predeterminado." << std::endl;
        }
        
        Libro* nuevoLibro = new Libro(titulo, autor, codigo, ubicacion, genero, copias);
        arbolLibros->insertar(nuevoLibro);
    }
    
    file.close();
    std::cout << "Libros cargados correctamente desde " << LIBROS_FILE << std::endl;
    return true;
}

// Similar manejo de excepciones debería añadirse en cargarPrestamos() para currentId

// Métodos para usuarios
bool DatabaseManager::guardarUsuarios() {
    std::ofstream file(USUARIOS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << USUARIOS_FILE << " para escritura." << std::endl;
        return false;
    }
    
    std::vector<Usuario*> usuarios = hashUsuarios->obtenerTodosUsuarios();
    
    for (Usuario* usuario : usuarios) {
        // Determinar si es admin
        std::string tipo = hashUsuarios->esAdmin(usuario->getIdUsuario()) ? "A" : "U";
        
        file << tipo << ";"
             << usuario->getIdUsuario() << ";"
             << usuario->getNombre() << ";"
             << usuario->getContacto() << ";"
             << usuario->getContrasena() << std::endl;
    }
    
    file.close();
    std::cout << "Usuarios guardados correctamente en " << USUARIOS_FILE << std::endl;
    return true;
}

bool DatabaseManager::cargarUsuarios() {
    std::ifstream file(USUARIOS_FILE);
    if (!file.is_open()) {
        std::cerr << "Advertencia: No se pudo abrir el archivo " << USUARIOS_FILE << " para lectura." << std::endl;
        return false;
    }
    
    std::string linea;
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string tipo, id, nombre, contacto, contrasena;
        
        std::getline(ss, tipo, ';');
        std::getline(ss, id, ';');
        std::getline(ss, nombre, ';');
        std::getline(ss, contacto, ';');
        std::getline(ss, contrasena, ';');
        
        Usuario* nuevoUsuario;
        
        if (tipo == "A") {
            nuevoUsuario = new Administrador(id, nombre, contacto, contrasena);
        } else { // tipo == "U"
            nuevoUsuario = new Usuario(id, nombre, contacto, contrasena);
        }
        
        hashUsuarios->insert(nuevoUsuario);
    }
    
    file.close();
    std::cout << "Usuarios cargados correctamente desde " << USUARIOS_FILE << std::endl;
    return true;
}

// Métodos para préstamos
bool DatabaseManager::guardarPrestamos() {
    std::ofstream file(PRESTAMOS_FILE);
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << PRESTAMOS_FILE << " para escritura." << std::endl;
        return false;
    }
    
    std::vector<Prestamo> prestamos = prestamoManager->obtenerTodosLosPrestamos();
    
    for (const Prestamo& prestamo : prestamos) {
        file << prestamo.getIdPrestamo() << ";"
             << prestamo.getIdUsuario() << ";"
             << prestamo.getIdLibro() << ";"
             << prestamo.getFechaPrestamo() << ";"
             << prestamo.getFechaDevolucion() << ";"
             << prestamo.getEstado() << std::endl;

    }
    file.close();
    std::cout << "Prestamos guardados correctamente en " << PRESTAMOS_FILE << std::endl;
    //guardar el backup diario
    guardarBackupDiario();
    return true;
}

bool DatabaseManager::cargarPrestamos() {
    std::ifstream file(PRESTAMOS_FILE);
    if (!file.is_open()) {
        std::cerr << "Advertencia: No se pudo abrir el archivo " << PRESTAMOS_FILE << " para lectura." << std::endl;
        return false;
    }
    
    std::string linea;
    int maxId = 0;
    
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::string idPrestamo, idUsuario, idLibro, fechaPrestamo, fechaDevolucion, estado;
        
        std::getline(ss, idPrestamo, ';');
        std::getline(ss, idUsuario, ';');
        std::getline(ss, idLibro, ';');
        std::getline(ss, fechaPrestamo, ';');
        std::getline(ss, fechaDevolucion, ';');
        std::getline(ss, estado, ';');

        Prestamo nuevoPrestamo(idPrestamo, idUsuario, idLibro, fechaPrestamo, fechaDevolucion, estado);
        historialPrestamos->insertar(nuevoPrestamo);
        
        // Extraer el número del ID para actualizar el contador
        int currentId = std::stoi(idPrestamo.substr(1));
        if (currentId > maxId) {
            maxId = currentId;
        }
        
        // Si el préstamo está activo, actualizar las copias disponibles del libro
        if (estado == "Activo") {
            Libro* libro = arbolLibros->buscar(idLibro);
            if (libro) {
                libro->setCopiasDisponibles(libro->getCopiasDisponibles() - 1);
            }
        }
    }
    
    // Establecer el contador de ID en PrestamoManager
    prestamoManager->setContadorIdPrestamo(maxId);
    
    
    file.close();
    std::cout << "Prestamos cargados correctamente desde " << PRESTAMOS_FILE << std::endl;
    return true;
}

// Método para guardar todos los datos
bool DatabaseManager::guardarTodo() {
    bool librosOk = guardarLibros();
    bool usuariosOk = guardarUsuarios();
    bool prestamosOk = guardarPrestamos();
    
    return librosOk && usuariosOk && prestamosOk;
}

// Método para cargar todos los datos
bool DatabaseManager::cargarTodo() {
    bool librosOk = cargarLibros();
    bool usuariosOk = cargarUsuarios();
    bool prestamosOk = cargarPrestamos();
    
    return librosOk && usuariosOk && prestamosOk;
}

std::string DatabaseManager::obtenerNombreBackupDiario() {
    // Obtener la fecha actual
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    
    std::tm local_tm = *std::localtime(&now_time);
    
    // Formatear como YYYYMMDD.txt (sin incluir la hora)
    std::stringstream ss;
    ss << BACKUP_PATH  // Usar la ruta de backups
       << (local_tm.tm_year + 1900) 
       << std::setw(2) << std::setfill('0') << (local_tm.tm_mon + 1) 
       << std::setw(2) << std::setfill('0') << local_tm.tm_mday 
       << ".txt";
    
    return ss.str();
}

bool DatabaseManager::esArchivoBackup(const std::string& nombreArchivo) {
    // Verificar si el nombre tiene formato YYYYMMDD.txt
    if (nombreArchivo.length() != 12) { // 8 dígitos + .txt
        return false;
    }
    
    // Verificar si termina en .txt
    if (nombreArchivo.substr(nombreArchivo.length() - 4) != ".txt") {
        return false;
    }
    
    // Verificar si los primeros 8 caracteres son dígitos
    for (int i = 0; i < 8; i++) {
        if (!std::isdigit(nombreArchivo[i])) {
            return false;
        }
    }
    
    return true;
}

bool DatabaseManager::guardarBackupDiario() {
    std::string nombreBackup = obtenerNombreBackupDiario();
    
    #ifdef _WIN32
    std::string comando = "mkdir \"" + BACKUP_PATH + "\" 2> nul";
    system(comando.c_str());
    #else
    std::string comando = "mkdir -p \"" + BACKUP_PATH + "\"";
    system(comando.c_str());
    #endif


    // Guardamos los préstamos en el archivo de backup diario
    std::ofstream file(nombreBackup);  // Siempre sobrescribimos el archivo del día
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreBackup << " para escritura." << std::endl;
        return false;
    }
    
    std::vector<Prestamo> prestamos = prestamoManager->obtenerTodosLosPrestamos();
    
    for (const Prestamo& prestamo : prestamos) {
        file << prestamo.getIdPrestamo() << ";"
             << prestamo.getIdUsuario() << ";"
             << prestamo.getIdLibro() << ";"
             << prestamo.getFechaPrestamo() << ";"
             << prestamo.getFechaDevolucion() << ";"
             << prestamo.getEstado() << std::endl;
    }
    
    file.close();
    std::cout << "Backup diario actualizado correctamente en " << nombreBackup << std::endl;
    return true;
}

std::vector<std::string> DatabaseManager::obtenerListaBackups() {
    std::vector<std::string> listaBackups;
    
    // Asegurarse de que el directorio existe
    #ifdef _WIN32
    std::string comando = "mkdir \"" + BACKUP_PATH + "\" 2> nul";
    system(comando.c_str());
    #else
    std::string comando = "mkdir -p \"" + BACKUP_PATH + "\"";
    system(comando.c_str());
    #endif
    
    #ifdef _WIN32
    // Código para Windows
    WIN32_FIND_DATA fileData;
    std::string searchPath = BACKUP_PATH + "*.txt";
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &fileData);
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string filename = fileData.cFileName;
            if (esArchivoBackup(filename)) {
                listaBackups.push_back(BACKUP_PATH + filename);  // Solo guardamos el nombre, no la ruta
            }
        } while (FindNextFile(hFind, &fileData));
        FindClose(hFind);
    }
    #else
    // Código para sistemas tipo Unix
    #include <dirent.h>
    DIR* dir = opendir(BACKUP_PATH.c_str());
    if (dir != NULL) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            std::string filename = entry->d_name;
            if (esArchivoBackup(filename)) {
                listaBackups.push_back(filename);  // Solo guardamos el nombre, no la ruta
            }
        }
        closedir(dir);
    }
    #endif
    
    // Ordenar los backups por fecha
    std::sort(listaBackups.begin(), listaBackups.end());
    
    return listaBackups;
}

bool DatabaseManager::cargarBackupEspecifico(const std::string& rutaCompleta) {
    std::ifstream archivoBackup(rutaCompleta);
    try {
        
        // Intentar abrir el archivo
        std::ifstream archivoBackup(rutaCompleta);
        if (!archivoBackup.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo de backup " << rutaCompleta << std::endl;
            return false;
        }
        
        std::cout << "Archivo de backup abierto correctamente. Iniciando carga de datos..." << std::endl;
        
        // Resetear el historial de préstamos
        if (historialPrestamos) {
            // En lugar de borrar y crear un nuevo objeto, vamos a recorrer la lista y eliminar los nodos
            // Esto para evitar posibles problemas de memoria
            Nodo* actual = historialPrestamos->getCabeza();
            if (actual) {
                do {
                    historialPrestamos->eliminar(actual->prestamo.getIdPrestamo());
                    actual = historialPrestamos->getCabeza();
                } while (actual != nullptr && !historialPrestamos->estaVacia());
            }
        }
        
        // Leer el archivo de backup línea por línea
        std::string linea;
        int contadorPrestamos = 0;
        
        while (std::getline(archivoBackup, linea)) {
            try {
                std::stringstream ss(linea);
                std::string idPrestamo, idUsuario, idLibro, fechaPrestamo, fechaDevolucion, estado;
                
                std::getline(ss, idPrestamo, ';');
                std::getline(ss, idUsuario, ';');
                std::getline(ss, idLibro, ';');
                std::getline(ss, fechaPrestamo, ';');
                std::getline(ss, fechaDevolucion, ';');
                std::getline(ss, estado, ';');
                
                // Verificar que tenemos todos los datos necesarios
                if (idPrestamo.empty() || idUsuario.empty() || idLibro.empty() || 
                    fechaPrestamo.empty() || fechaDevolucion.empty() || estado.empty()) {
                    std::cerr << "Advertencia: Linea mal formada en el backup: " << linea << std::endl;
                    continue;
                }
                
                Prestamo nuevoPrestamo(idPrestamo, idUsuario, idLibro, fechaPrestamo, fechaDevolucion, estado);
                historialPrestamos->insertar(nuevoPrestamo);
                contadorPrestamos++;
                
                // Extraer el número del ID para actualizar el contador
                if (idPrestamo.length() > 1) {
                    try {
                        int currentId = std::stoi(idPrestamo.substr(1));
                        if (currentId > prestamoManager->getContadorIdPrestamo()) {
                            prestamoManager->setContadorIdPrestamo(currentId);
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Error al procesar ID de prestamo: " << idPrestamo << std::endl;
                    }
                }
                
                // Si el préstamo está activo, actualizar las copias disponibles del libro
                if (estado == "Activo") {
                    Libro* libro = arbolLibros->buscar(idLibro);
                    if (libro) {
                        libro->setCopiasDisponibles(libro->getCopiasDisponibles() - 1);
                    }
                }
            } catch (const std::exception& e) {
                std::cerr << "Excepcion al cargar backup: " << e.what() << std::endl;
                return false;
            }
        }
        
        archivoBackup.close();
        
        std::cout << "Se cargaron " << contadorPrestamos << " prestamos desde el backup." << std::endl;
        
        // Actualizar el archivo prestamos.txt
        bool resultado = guardarPrestamos();
        if (resultado) {
            std::cout << "Datos de backup sincronizados con prestamos.txt" << std::endl;
        } else {
            std::cerr << "Error al sincronizar datos con prestamos.txt" << std::endl;
        }
        
        return contadorPrestamos > 0;
    } catch (const std::exception& e) {
        std::cerr << "Excepcion al cargar backup: " << e.what() << std::endl;
        return false;
    }
}

std::string DatabaseManager::formatearNombreBackup(const std::string& rutaCompleta) {
    size_t ultimaBarra = rutaCompleta.find_last_of("/\\");
    std::string nombreArchivo;
    if (ultimaBarra != std::string::npos) {
        nombreArchivo = rutaCompleta.substr(ultimaBarra + 1);
    } else {
        nombreArchivo = rutaCompleta;
    }
    // Extraer la fecha del nombre (formato esperado: YYYYMMDD.txt)
    if (nombreArchivo.length() >= 12 && nombreArchivo.substr(nombreArchivo.length() - 4) == ".txt") {
        std::string fechaStr = nombreArchivo.substr(0, 8);
        
        // Formatear como DD/MM/YYYY
        std::string dia = fechaStr.substr(6, 2);
        std::string mes = fechaStr.substr(4, 2);
        std::string anio = fechaStr.substr(0, 4);
        
        return "Backup del " + dia + "/" + mes + "/" + anio;
    }
    
    return nombreArchivo; // Si no se puede formatear, devolver el original
}
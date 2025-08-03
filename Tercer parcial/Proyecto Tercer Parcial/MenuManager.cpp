#include "MenuManager.h"

MenuManager::MenuManager(HashUsuario* hashUsuarios, ArbolAVL* arbolLibros, 
    PrestamoManager* prestamoManager, DatabaseManager* dbManager)
: hashUsuarios(hashUsuarios), arbolLibros(arbolLibros), 
prestamoManager(prestamoManager), dbManager(dbManager), recomendacionManager(nullptr) {
// Inicializamos el recomendador como nulo, se creará cuando sea necesario
}

MenuManager::~MenuManager() {
    // Liberar memoria del recomendador si existe
    if (recomendacionManager) {
        delete recomendacionManager;
    }
}

void MenuManager::inicializarRecomendador() {
    // Crear el recomendador si no existe
    if (!recomendacionManager) {
        recomendacionManager = new RecomendacionManager(prestamoManager, arbolLibros, hashUsuarios);
    }
    
    // Inicializar con los datos actuales
    recomendacionManager->inicializar();
    
    std::cout << "Sistema de recomendaciones inicializado correctamente." << std::endl;
}

void MenuManager::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void MenuManager::pausa() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
    limpiarPantalla();
}
void MenuManager::mostrarRecomendacionesPersonalizadas(Usuario* usuario) {
    // Verificar que el recomendador exista
    if (!recomendacionManager) {
        inicializarRecomendador();
    }
    
    std::cout << "\n===== RECOMENDACIONES PERSONALIZADAS PARA " << usuario->getNombre() << " =====\n";
    
    // Obtener el historial de préstamos para ver qué géneros le gustan al usuario
    std::vector<Prestamo> historialUsuario = 
        prestamoManager->obtenerHistorialPrestamoUsuario(usuario->getIdUsuario());
    
    if (historialUsuario.empty()) {
        std::cout << "No tienes un historial de prestamos suficiente para generar recomendaciones personalizadas.\n";
        std::cout << "¡Comienza pidiendo algunos libros!\n";
        return;
    }
    
    // Asegurarse de que el recomendador tenga los datos actualizados
    recomendacionManager->inicializar();
    
    // Mostrar información del perfil para que el usuario entienda por qué se recomiendan ciertos libros
    std::cout << "\nTu perfil de lectura:\n";
    recomendacionManager->mostrarPerfilUsuario(usuario->getIdUsuario());
    
    // Generar recomendaciones
    std::vector<Recomendacion> recomendaciones = 
        recomendacionManager->generarRecomendaciones(usuario->getIdUsuario(), 5);
    
    if (recomendaciones.empty()) {
        std::cout << "\nNo se encontraron libros disponibles para recomendar en este momento.\n";
        std::cout << "Intenta más tarde o habla con el bibliotecario.\n";
        return;
    }
    
    // Preparar datos para la tabla de recomendaciones
    std::vector<std::string> encabezados = {"Codigo", "Titulo", "Autor", "Genero", "Razones"};
    std::vector<std::vector<std::string>> datos;
    
    for (const Recomendacion& rec : recomendaciones) {
        Libro* libro = rec.libro;
        
        // Unir las razones en un solo string con comas
        std::string razonesStr;
        for (size_t i = 0; i < rec.razones.size(); i++) {
            razonesStr += rec.razones[i];
            if (i < rec.razones.size() - 1) {
                razonesStr += ", ";
            }
        }
        
        std::vector<std::string> fila = {
            libro->getCodigo(),
            libro->getTitulo(),
            libro->getAutor(),
            libro->getGenero(),
            razonesStr
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\nLibros recomendados para ti:\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
    
    // Opción para solicitar alguno de los libros recomendados
    std::string respuesta;
    std::cout << "\n¿Deseas solicitar alguno de estos libros? (s/n): ";
    std::cin >> respuesta;
    
    if (respuesta == "s" || respuesta == "S") {
        solicitarPrestamo(usuario);
    }
}

void MenuManager::configurarRecomendador() {
    // Verificar que el recomendador exista
    if (!recomendacionManager) {
        inicializarRecomendador();
    }
    
    // Opciones para el menú de configuración del recomendador
    std::vector<std::string> opcionesRecomendador = {
        "\033[33mConfigurar pesos manualmente\033[0m",
        "\033[33mEstablecer configuración predeterminada\033[0m",
        "\033[33mVer configuración actual\033[0m",
        "\033[33mRegenerar índice de recomendaciones\033[0m",
        "\033[33mVolver al menú anterior\033[0m"
    };
    
    while (true) {
        int opcion = mostrarMenuDinamico("\033[32m===== CONFIGURACION DEL SISTEMA DE RECOMENDACIONES =====\033[0m", opcionesRecomendador);
        
        double pesoHistorial, pesoPopularidad, pesoRelacion, pesoNovedades;
        int maxRecomendaciones;
        
        switch (opcion) {
            case 0: { // Configurar pesos manualmente
                system("cls");
                std::cout << "\n===== CONFIGURACION MANUAL DE PESOS =====\n";
                std::cout << "Nota: Los pesos deben sumar 1.0 (serán normalizados automáticamente).\n\n";
                
                std::cout << "Peso para el historial personal del usuario (0.0-1.0): ";
                std::cin >> pesoHistorial;
                
                std::cout << "Peso para la popularidad general de los libros (0.0-1.0): ";
                std::cin >> pesoPopularidad;
                
                std::cout << "Peso para las relaciones entre géneros (0.0-1.0): ";
                std::cin >> pesoRelacion;
                
                std::cout << "Peso para la novedad de los libros (0.0-1.0): ";
                std::cin >> pesoNovedades;
                
                std::cout << "Número máximo de recomendaciones a generar: ";
                std::cin >> maxRecomendaciones;
                
                // Verificar valores de entrada
                if (pesoHistorial < 0 || pesoPopularidad < 0 || pesoRelacion < 0 || pesoNovedades < 0) {
                    std::cout << "Error: Los pesos no pueden ser negativos. Se usarán valores predeterminados.\n";
                    pesoHistorial = 0.4;
                    pesoPopularidad = 0.3;
                    pesoRelacion = 0.2;
                    pesoNovedades = 0.1;
                }
                
                if (maxRecomendaciones <= 0) {
                    std::cout << "Error: El número de recomendaciones debe ser positivo. Se usará 5 por defecto.\n";
                    maxRecomendaciones = 5;
                }
                
                // Configurar el recomendador con los parámetros especificados
                recomendacionManager->configurarParametros(
                    pesoHistorial, pesoPopularidad, pesoRelacion, pesoNovedades, maxRecomendaciones);
                
                // Mostrar la configuración final (después de normalización)
                double sumaTotal = pesoHistorial + pesoPopularidad + pesoRelacion + pesoNovedades;
                std::cout << "\nConfiguración aplicada (valores normalizados):\n";
                std::cout << "- Peso historial personal: " << std::fixed << std::setprecision(2) 
                          << (pesoHistorial / sumaTotal) << "\n";
                std::cout << "- Peso popularidad: " << std::fixed << std::setprecision(2) 
                          << (pesoPopularidad / sumaTotal) << "\n";
                std::cout << "- Peso relaciones entre géneros: " << std::fixed << std::setprecision(2) 
                          << (pesoRelacion / sumaTotal) << "\n";
                std::cout << "- Peso novedades: " << std::fixed << std::setprecision(2) 
                          << (pesoNovedades / sumaTotal) << "\n";
                std::cout << "- Máximo de recomendaciones: " << maxRecomendaciones << "\n";
                
                std::cout << "\nConfiguración guardada correctamente.\n";
                pausa();
                break;
            }
            case 1: { // Establecer configuración predeterminada
                system("cls");
                std::cout << "\nAplicando configuración predeterminada...\n";
                
                pesoHistorial = 0.4;
                pesoPopularidad = 0.3;
                pesoRelacion = 0.2;
                pesoNovedades = 0.1;
                maxRecomendaciones = 5;
                
                recomendacionManager->configurarParametros(
                    pesoHistorial, pesoPopularidad, pesoRelacion, pesoNovedades, maxRecomendaciones);
                
                std::cout << "\nConfiguración predeterminada aplicada:\n";
                std::cout << "- Peso historial personal: 0.40\n";
                std::cout << "- Peso popularidad: 0.30\n";
                std::cout << "- Peso relaciones entre géneros: 0.20\n";
                std::cout << "- Peso novedades: 0.10\n";
                std::cout << "- Máximo de recomendaciones: 5\n";
                
                pausa();
                break;
            }
            case 2: { // Ver configuración actual
                system("cls");
                std::cout << "\n===== CONFIGURACIÓN ACTUAL DEL RECOMENDADOR =====\n";
                
                // Agregar los métodos getter en RecomendacionManager para obtener los valores actuales
                std::cout << "Pesos actuales del algoritmo de recomendación:\n";
                std::cout << "- Peso historial personal: " << std::fixed << std::setprecision(2) 
                          << recomendacionManager->getPesoHistorialPersonal() << "\n";
                std::cout << "- Peso popularidad: " << std::fixed << std::setprecision(2) 
                          << recomendacionManager->getPesoPopularidad() << "\n";
                std::cout << "- Peso relaciones entre géneros: " << std::fixed << std::setprecision(2) 
                          << recomendacionManager->getPesoRelacionGeneros() << "\n";
                std::cout << "- Peso novedades: " << std::fixed << std::setprecision(2) 
                          << recomendacionManager->getPesoNovedades() << "\n";
                std::cout << "- Máximo de recomendaciones: " 
                          << recomendacionManager->getMaxRecomendaciones() << "\n";
                
                pausa();
                break;
            }
            case 3: { // Regenerar índice de recomendaciones
                system("cls");
                std::cout << "\nRegenerando índice de recomendaciones...\n";
                
                // Reinicializar el recomendador
                recomendacionManager->inicializar();
                
                std::cout << "El índice de recomendaciones ha sido regenerado correctamente.\n";
                std::cout << "Esta operación analiza todo el historial de préstamos y recalcula:\n";
                std::cout << "- Perfiles de interés de usuarios\n";
                std::cout << "- Relaciones entre géneros literarios\n";
                std::cout << "- Popularidad de los libros\n";
                
                pausa();
                break;
            }
            case 4: // Volver al menú anterior
            case -1: // Escape presionado
                return;
            default:
                std::cout << "Opción no válida.\n";
                pausa();
        }
    }
}

void MenuManager::modificarPerfilUsuario(Usuario* usuario) {
    std::vector<std::string> opcionesPerfil = {
        "\033[33mModificar nombre\033[0m",
        "\033[33mModificar contacto\033[0m",
        "\033[33mModificar contraseña\033[0m",
        "\033[33mVolver al menu anterior\033[0m"
    };
    
    bool datosModificados = false;  // Variable para seguir si hubo cambios
    
    while (true) {
        // Mostrar los datos actuales del usuario antes del menú
        system("cls");
        std::cout << "\n===== DATOS ACTUALES DEL USUARIO =====\n";
        std::cout << "Nombre: " << usuario->getNombre() << "\n";
        std::cout << "Contacto: " << usuario->getContacto() << "\n";
        std::cout << "Contraseña: *******\n\n";
        
        int opcion = mostrarMenuDinamico("===== MODIFICAR PERFIL DE USUARIO =====", opcionesPerfil);
        
        std::string nuevoNombre, nuevoContacto, nuevaContrasena, confirmarContrasena;
        
        switch (opcion) {
            case 0: { // Modificar nombre
                system("cls");
                std::string nuevoNombre;
                std::cout << "Nombre actual: " << usuario->getNombre() << "\n";
                
                nuevoNombre = Validacion::capturarNombreAutor("Ingrese nuevo nombre: ");
                
                usuario->setNombre(nuevoNombre);
                std::cout << "Nombre actualizado correctamente.\n";
                datosModificados = true;
                
                pausa();
                break;
            }
            case 1: { // Modificar contacto
                system("cls");
                std::string nuevoContacto;
                std::cout << "Contacto actual: " << usuario->getContacto() << "\n";
                while (true) {
                    std::cout << "Ingrese nuevo contacto: ";
                    std::getline(std::cin, nuevoContacto);
                    
                    if (!Validacion::validarCorreo(nuevoContacto)) {
                        std::cout << "Correo electrónico inválido.\n";
                        continue;
                    }
                    
                    usuario->setContacto(nuevoContacto);
                    std::cout << "Contacto actualizado correctamente.\n";
                    datosModificados = true;
                    break;
                }
                
                pausa();
                break;
            }
            case 2: { // Modificar contraseña
                system("cls");
                std::cout << "Ingrese contraseña actual: ";
                std::cin.ignore();
                std::getline(std::cin, nuevaContrasena);
                
                if (usuario->verificarContrasena(nuevaContrasena)) {
                    std::cout << "Ingrese nueva contraseña: ";
                    std::getline(std::cin, nuevaContrasena);
                    
                    std::cout << "Confirme nueva contraseña: ";
                    std::getline(std::cin, confirmarContrasena);
                    
                    if (nuevaContrasena == confirmarContrasena) {
                        if (!nuevaContrasena.empty()) {
                            usuario->setContrasena(nuevaContrasena);
                            std::cout << "Contraseña actualizada correctamente.\n";
                            datosModificados = true;
                        } else {
                            std::cout << "La contraseña no puede estar vacía.\n";
                        }
                    } else {
                        std::cout << "Las contraseñas no coinciden.\n";
                    }
                } else {
                    std::cout << "Contraseña actual incorrecta.\n";
                }
                pausa();
                break;
            }
            case 3: // Volver al menú anterior
            case -1: { // Escape presionado
                // Guardar los cambios si se modificaron datos
                if (datosModificados && dbManager) {
                    dbManager->guardarUsuarios();
                    std::cout << "Los cambios han sido guardados.\n";
                    pausa();
                }
                return;
            }
            default:
                std::cout << "Opcion no válida.\n";
                pausa();
        }
    }
}
void MenuManager::gestionarUsuarios() {
    // Opciones del menú de gestión de usuarios
    std::vector<std::string> opcionesGestionUsuarios = {
        "\033[33mMostrar todos los usuarios\033[0m",
        "\033[33mBuscar usuario\033[0m",
        "\033[33mEliminar usuario\033[0m",
        "\033[33mVolver al menu anterior\033[0m"
    };
    
    while (true) {
        int opcion = mostrarMenuDinamico("\033[32m===== GESTION DE USUARIOS =====\033[0m", opcionesGestionUsuarios);
        
        switch (opcion) {
            case 0: // Mostrar todos los usuarios
                system("cls"); // Limpiar pantalla para mostrar la información
                std::cout << "\n===== TODOS LOS USUARIOS =====\n";
                hashUsuarios->display();
                pausa();
                break;
            case 1: { // Buscar usuario
                system("cls");
                std::string id;
                std::cout << "Ingrese el ID del usuario a buscar: ";
                std::cin >> id;
                
                Usuario* usuario = hashUsuarios->find(id);
                if (usuario) {
                    // Definir encabezados
                    std::vector<std::string> encabezados = {"Atributo", "Valor"};
                    
                    // Preparar datos para la tabla
                    std::vector<std::vector<std::string>> datos = {
                        {"ID", usuario->getIdUsuario()},
                        {"Nombre", usuario->getNombre()},
                        {"Contacto", usuario->getContacto()},
                        {"Tipo", hashUsuarios->esAdmin(id) ? "Administrador" : "Usuario regular"}
                    };
                    
                    // Calcular anchos óptimos para cada columna
                    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
                    
                    // Imprimir la tabla
                    std::cout << "\n===== USUARIO ENCONTRADO =====\n";
                    
                    imprimirLineaHorizontal(anchos);
                    imprimirFilaTabla(encabezados, anchos);
                    imprimirLineaHorizontal(anchos);
                    
                    for (const auto& fila : datos) {
                        imprimirFilaTabla(fila, anchos);
                    }
                    
                    imprimirLineaHorizontal(anchos);
                } else {
                    std::cout << "Usuario no encontrado.\n";
                }
                pausa();
                break;
            }
            case 2: { // Eliminar usuario
                system("cls");
                std::string id;
                std::cout << "Ingrese el ID del usuario a eliminar: ";
                std::cin >> id;
                
                // Preguntar confirmación
                char confirmar;
                std::cout << "¿Está seguro de eliminar el usuario con ID " << id << "? (s/n): ";
                std::cin >> confirmar;
                
                if (confirmar == 's' || confirmar == 'S') {
                    if (hashUsuarios->remove(id)) {
                        std::cout << "Usuario eliminado correctamente.\n";
                        // Guardar cambios si hay un dbManager
                        if (dbManager) {
                            dbManager->guardarUsuarios();
                        }
                    } else {
                        std::cout << "No se pudo eliminar el usuario.\n";
                    }
                } else {
                    std::cout << "Operación cancelada.\n";
                }
                pausa();
                break;
            }
            case 3: // Volver al menú anterior
            case -1: // Escape presionado
                return;
            default:
                std::cout << "Opcion no válida.\n";
                pausa();
        }
    }
}

void MenuManager::gestionarLibros() {
    // Opciones para el menú de gestión de libros
    std::vector<std::string> opcionesGestionLibros = {
        "\033[33mMostrar todos los libros\033[0m",
        "\033[33mBuscar libro\033[0m",
        "\033[33mAñadir nuevo libro\033[0m",
        "\033[33mModificar libro\033[0m",
        "\033[33mEliminar libro\033[0m",
        "\033[33mVolver al menú anterior\033[0m"
    };
    
    while (true) {
        int opcion = mostrarMenuDinamico("\033[32m===== GESTION DE LIBROS =====\033[0m", opcionesGestionLibros);
        
        switch (opcion) {
            case 0: { // Mostrar todos los libros
                system("cls");
                std::vector<Libro*> libros = arbolLibros->inOrden();
                
                if (libros.empty()) {
                    std::cout << "No hay libros registrados en el sistema." << std::endl;
                    pausa();
                    break;
                }
                
                // Definir encabezados
                std::vector<std::string> encabezados = {"Codigo", "Titulo", "Autor", "Ubicacion", "Genero", "Copias"};
                
                // Preparar datos para la tabla
                std::vector<std::vector<std::string>> datos;
                
                for (Libro* libro : libros) {
                    std::vector<std::string> fila = {
                        libro->getCodigo(),
                        libro->getTitulo(),
                        libro->getAutor(),
                        libro->getUbicacion(),
                        libro->getGenero(),
                        std::to_string(libro->getCopiasDisponibles())
                    };
                    
                    datos.push_back(fila);
                }
                
                // Calcular anchos óptimos para cada columna
                std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
                
                // Imprimir la tabla
                std::cout << "\n===== TODOS LOS LIBROS =====\n";
                
                imprimirLineaHorizontal(anchos);
                imprimirFilaTabla(encabezados, anchos);
                imprimirLineaHorizontal(anchos);
                
                for (const auto& fila : datos) {
                    imprimirFilaTabla(fila, anchos);
                }
                
                imprimirLineaHorizontal(anchos);
                
                pausa();
                break;
            }
            case 1: { // Buscar libro
                system("cls");
                std::string codigo;
                std::cout << "Ingrese el codigo del libro a buscar: ";
                std::cin >> codigo;
                
                Libro* libro = arbolLibros->buscar(codigo);
                if (libro) {
                    // Definir encabezados
                    std::vector<std::string> encabezados = {"Atributo", "Valor"};
                    
                    // Preparar datos para la tabla
                    std::vector<std::vector<std::string>> datos = {
                        {"Código", libro->getCodigo()},
                        {"Título", libro->getTitulo()},
                        {"Autor", libro->getAutor()},
                        {"Ubicación", libro->getUbicacion()},
                        {"Género", libro->getGenero()},
                        {"Copias disponibles", std::to_string(libro->getCopiasDisponibles())}
                    };
                    
                    // Calcular anchos óptimos para cada columna
                    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
                    
                    // Imprimir la tabla
                    std::cout << "\n===== LIBRO ENCONTRADO =====\n";
                    
                    imprimirLineaHorizontal(anchos);
                    imprimirFilaTabla(encabezados, anchos);
                    imprimirLineaHorizontal(anchos);
                    
                    for (const auto& fila : datos) {
                        imprimirFilaTabla(fila, anchos);
                    }
                    
                    imprimirLineaHorizontal(anchos);
                } else {
                    std::cout << "Libro no encontrado.\n";
                }
                pausa();
                break;
            }
            case 2: { // Añadir nuevo libro
                system("cls");
                std::string codigo, titulo, autor, ubicacion, genero;
                int copias;
                
                std::cout << "===== AÑADIR NUEVO LIBRO =====\n\n";
                std::cout << "El código del libro debe tener el formato LXXX donde X son números.\n";
                std::cout << "Por ejemplo: L001, L123, etc.\n\n";
                
                codigo = Validacion::capturarCodigoLibro("Ingrese el código del nuevo libro: ");
                
                // Verificar si ya existe un libro con ese código
                if (arbolLibros->buscar(codigo)) {
                    std::cout << "Ya existe un libro con ese código.\n";
                    pausa();
                    break;
                }
                
                std::cout << "Ingrese el título: ";
                std::cin.ignore();
                std::getline(std::cin, titulo);
                
                autor = Validacion::capturarNombreAutor("Ingrese el autor: ");
                
                std::cout << "Ingrese la ubicación: ";
                std::getline(std::cin, ubicacion);
                
                std::cout << "Ingrese el género: ";
                std::getline(std::cin, genero);
            
                std::cout << "Ingrese el número de copias disponibles: ";
                std::cin >> copias;
                
                Libro* nuevoLibro = new Libro(titulo, autor, codigo, ubicacion, genero, copias);
                arbolLibros->insertar(nuevoLibro);
                
                std::cout << "Libro agregado correctamente.\n";
                
                // Guardar los datos actualizados
                if (dbManager) {
                    dbManager->guardarLibros();
                }
                
                pausa();
                break;
            }
            case 3: { // Modificar libro
                system("cls");
                std::string codigo, titulo, autor, ubicacion, genero;
                int copias;
                
                std::cout << "Ingrese el codigo del libro a modificar: ";
                std::cin >> codigo;
                
                Libro* libro = arbolLibros->buscar(codigo);
                if (!libro) {
                    std::cout << "Libro no encontrado.\n";
                    pausa();
                    break;
                }
                
                std::cout << "Modificando libro: " << libro->getTitulo() << "\n";
                
                std::cout << "Nuevo titulo (deje en blanco para mantener actual: " << libro->getTitulo() << "): ";
                std::cin.ignore();
                std::getline(std::cin, titulo);
                if (!titulo.empty()) {
                    libro->setTitulo(titulo);
                }
                
                autor = Validacion::capturarNombreAutor("Nuevo autor (deje en blanco para mantener actual: " + 
                libro->getAutor() + "): ");
                if (!autor.empty()) {
                libro->setAutor(autor);
                }
                
                std::cout << "Nueva ubicacion (deje en blanco para mantener actual: " << libro->getUbicacion() << "): ";
                std::getline(std::cin, ubicacion);
                if (!ubicacion.empty()) {
                    libro->setUbicacion(ubicacion);
                }
            
                std::cout << "Nuevo genero (deje en blanco para mantener actual: " << libro->getGenero() << "): ";
                std::getline(std::cin, genero);
                if (!genero.empty()) {
                    libro->setGenero(genero);
                }
                
                std::cout << "Nuevo numero de copias (0 para mantener actual: " << libro->getCopiasDisponibles() << "): ";
                std::cin >> copias;
                if (copias > 0) {
                    libro->setCopiasDisponibles(copias);
                }
                
                std::cout << "Libro modificado correctamente.\n";
                
                // Guardar los datos actualizados
                if (dbManager) {
                    dbManager->guardarLibros();
                }
                
                pausa();
                break;
            }
            case 4: { // Eliminar libro
                system("cls");
                std::string codigo;
                std::cout << "Ingrese el codigo del libro a eliminar: ";
                std::cin >> codigo;
                
                // Verificar que el libro existe
                Libro* libro = arbolLibros->buscar(codigo);
                if (!libro) {
                    std::cout << "Error: El libro con código " << codigo << " no existe.\n";
                    pausa();
                    break;
                }
                
                // Verificar si hay préstamos activos para este libro
                std::vector<Prestamo> todosLosPrestamos = getPrestamoManager()->obtenerTodosLosPrestamos();
                bool tienePrestamoActivo = false;
                
                for (const auto& prestamo : todosLosPrestamos) {
                    if (prestamo.getIdLibro() == codigo && prestamo.getEstado() == "Activo") {
                        tienePrestamoActivo = true;
                        break;
                    }
                }
                
                if (tienePrestamoActivo) {
                    std::cout << "Error: No se puede eliminar el libro porque tiene prestamos activos.\n";
                    pausa();
                    break;
                }
                
                // Preguntar por confirmación
                char confirmar;
                std::cout << "\n¿Esta seguro de eliminar el libro \"" << libro->getTitulo() << "\" de " 
                          << libro->getAutor() << "? (s/n): ";
                std::cin >> confirmar;
                
                if (confirmar == 's' || confirmar == 'S') {
                    // Guardar una copia de los datos para mostrar un mensaje después
                    std::string tituloLibro = libro->getTitulo();
                    
                    // Eliminar el libro del árbol AVL
                    arbolLibros->eliminar(codigo);
                    
                    std::cout << "El libro \"" << tituloLibro << "\" ha sido eliminado correctamente.\n";
                    
                    // Guardar los datos actualizados
                    if (dbManager) {
                        dbManager->guardarLibros();
                    }
                } else {
                    std::cout << "Operacion cancelada.\n";
                }
                pausa();
                break;
            }
            case 5: // Volver al menú anterior
            case -1: // Escape presionado
                return;
            default:
                std::cout << "Opcion no valida.\n";
                pausa();
        }
    }
}


void MenuManager::cargarLibrosEjemplo() {
    // Agregamos algunos libros de ejemplo
// Cambiar las líneas donde se crean los libros de ejemplo, por ejemplo:
    arbolLibros->insertar(new Libro("El Quijote", "Miguel de Cervantes", "L001", "Sección A, Estante 1", "Clásico", 3));
    arbolLibros->insertar(new Libro("Cien años de soledad", "Gabriel García Márquez", "L002", "Sección B, Estante 3", "Realismo Mágico", 2));
    arbolLibros->insertar(new Libro("El principito", "Antoine de Saint-Exupéry", "L003", "Sección C, Estante 2", "Infantil", 5));
    arbolLibros->insertar(new Libro("1984", "George Orwell", "L004", "Sección A, Estante 4", "Distopía", 1));
    arbolLibros->insertar(new Libro("Rayuela", "Julio Cortázar", "L005", "Sección B, Estante 1", "Experimental", 2));
    
    std::cout << "Se han cargado 5 libros de ejemplo en el sistema.\n";
}
bool MenuManager::iniciarSesion() {
    std::string id, contrasena;
    std::cout << "Ingrese su ID de usuario: ";
    std::cin >> id;
    std::cout << "Ingrese su contraseña: ";
    std::cin >> contrasena;
    
    Usuario* usuario = hashUsuarios->find(id);
    if (usuario && usuario->verificarContrasena(contrasena)) {
        std::cout << "\n¡Bienvenido, " << usuario->getNombre() << "!\n";
        pausa(); // Pausa para que el mensaje se vea antes de mostrar el menú
        
        if (hashUsuarios->esAdmin(id)) {
            // Menú de administrador con interfaz dinámica
            std::vector<std::string> opcionesAdmin = {
                "\033[33mGestionar usuarios\033[0m",
                "\033[33mGestionar libros\033[0m",
                "\033[33mVer todos los préstamos\033[0m",
                "\033[33mVer préstamos vencidos\033[0m",
                "\033[33mVer historial de préstamos de un usuario\033[0m",
                "\033[33mGenerar reporte general\033[0m",
                "\033[33mConfigurar sistema de recomendaciones\033[0m",
                "\033[33mCerrar sesión\033[0m"
            };
            
            while (true) {
                int opcionAdmin = mostrarMenuDinamico("\033[32m===== MENU DE ADMINISTRADOR =====\033[0m", opcionesAdmin);
                
                switch (opcionAdmin) {
                    case 0: // Gestionar usuarios
                        gestionarUsuarios();
                        break;
                    case 1: // Gestionar libros
                        gestionarLibros();
                        break;
                    case 2: // Ver todos los préstamos
                        mostrarTodosLosPrestamos();
                        pausa();
                        break;
                    case 3: // Ver préstamos vencidos
                        mostrarPrestamosVencidos();
                        pausa();
                        break;
                    case 4: { // Ver historial de usuario
                        std::string idUsuario;
                        std::cout << "Ingrese el ID del usuario: ";
                        std::cin >> idUsuario;
                        Usuario* usuarioFound = hashUsuarios->find(idUsuario);
                        if (usuarioFound) {
                            mostrarHistorialUsuarioParaAdmin(idUsuario);
                        } else {
                            std::cout << "Usuario no encontrado.\n";
                        }
                        pausa();
                        break;
                    }
                    case 5: // Generar reporte
                        generarReporteGeneral();
                        pausa();
                        break;
                    case 6: // Configurar recomendador
                        configurarRecomendador();
                        pausa();
                        break;
                    case 7: // Cerrar sesión
                    case -1: // Escape presionado
                        std::cout << "Cerrando sesión...\n";
                        return true;
                    default:
                        std::cout << "Opción no válida.\n";
                        pausa();
                }
            }
        } else {
            // Menú de usuario normal con interfaz dinámica
            std::vector<std::string> opcionesUsuario = {
                "\033[33mVer mis prestamos activos\033[0m",
                "\033[33mVer mi historial de préstamos\033[0m",
                "\033[33mSolicitar prestamo\033[0m",
                "\033[33mDevolver libro\033[0m",
                "\033[33mVer multas pendientes\033[0m",
                "\033[33mObtener recomendaciones personalizadas\033[0m",
                "\033[33mCambiar datos personales\033[0m",
                "\033[33mCerrar sesion\033[0m"
            };
            
            while (true) {
                int opcionUsuario = mostrarMenuDinamico("\033[32m===== MENU DE USUARIO =====\033[0m", opcionesUsuario);
                
                switch (opcionUsuario) {
                    case 0: // Ver préstamos activos
                        std::cout << "Prestamos activos de " << usuario->getNombre() << ":\n";
                        mostrarPrestamosActivos(usuario);
                        pausa();
                        break;
                    case 1: // Ver historial de préstamos
                        mostrarHistorialPrestamos(usuario);
                        pausa();
                        break;
                    case 2: // Solicitar préstamo
                        solicitarPrestamo(usuario);
                        pausa();
                        break;
                    case 3: // Devolver libro
                        devolverLibro(usuario);
                        pausa();
                        break;
                    case 4: // Ver multas
                        verMultasUsuario(usuario);
                        pausa();
                        break;
                    case 5: // Obtener recomendaciones
                        mostrarRecomendacionesPersonalizadas(usuario);
                        pausa();
                        break;
                    case 6: // Cambiar datos personales
                        modificarPerfilUsuario(usuario);
                        break;
                    case 7: // Cerrar sesión
                    case -1: // Escape presionado
                        std::cout << "Cerrando sesión...\n";
                        return true;
                    default:
                        std::cout << "Opcion no válida.\n";
                        pausa();
                }
            }
        }
    } else {
        std::cout << "ID o contraseña incorrectos.\n";
        pausa();
        return false;
    }
    
    return true;
}



bool MenuManager::registrarUsuario(bool esAdmin) {
    std::string id, nombre, contacto, contrasena;
    
    while (true) {
        id = Validacion::capturarIdAlfanumerico("Ingrese nuevo ID de " + 
            std::string(esAdmin ? "administrador" : "usuario") + ": ");
        
        // Verificar si el ID ya existe
        if (hashUsuarios->find(id)) {
            std::cout << "El ID ya existe. Por favor, elija otro.\n";
            continue;
        }
        break;
    }
    
    nombre = Validacion::capturarNombreAutor("Ingrese nombre: ");
    
    while (true) {
        std::cout << "Ingrese contacto (correo electrónico): ";
        std::getline(std::cin, contacto);
        
        // Validar correo
        if (!Validacion::validarCorreo(contacto)) {
            std::cout << "Correo electrónico inválido.\n";
            continue;
        }
        
        break;
    }
    
    while (true) {
        std::cout << "Ingrese contraseña: ";
        std::cin >> contrasena;
        
        // Validar contraseña
        if (!Validacion::validarContrasena(contrasena)) {
            std::cout << "Contraseña inválida. Debe tener al menos 6 caracteres.\n";
            continue;
        }
        
        break;
    }
    
    Usuario* nuevoUsuario;
    
    if (esAdmin) {
        nuevoUsuario = new Administrador(id, nombre, contacto, contrasena);
    } else {
        nuevoUsuario = new Usuario(id, nombre, contacto, contrasena);
    }
    
    if (hashUsuarios->insert(nuevoUsuario)) {
        std::cout << (esAdmin ? "Administrador" : "Usuario") << " registrado correctamente.\n";
        std::cout << "Puede iniciar sesión ahora con ID: " << id << " y su contraseña.\n";
        
        // Guardar los datos actualizados
        if (dbManager) {
            dbManager->guardarUsuarios();
        }
        
        pausa();
        return true;
    } else {
        std::cout << "Error al registrar el " << (esAdmin ? "administrador" : "usuario") << ".\n";
        delete nuevoUsuario;
        pausa();
        return false;
    }
}


void MenuManager::ejecutarMenuPrincipal() {
    while (true) {
        // Definir las opciones del menú principal
        std::vector<std::string> opciones = {
            "\033[33mIniciar sesion\033[0m",
            "\033[33mRegistrar nuevo usuario\033[0m",
            "\033[33mRegistrar nuevo administrador (demo)\033[0m",
            "\033[33mMostrar todos los usuarios registrados\033[0m",
            "\033[33mAyuda\033[0m",
            "\033[33mSalir\033[0m"
        };
        
        // Mostrar el menú dinámico
        int opcionPrincipal = mostrarMenuDinamico("\033[32m===== SISTEMA DE BIBLIOTECA =====\033[0m", opciones);
        
        switch (opcionPrincipal) {
            case 0: // Iniciar sesión
                iniciarSesion();
                break;
            case 1: // Registrar nuevo usuario
                registrarUsuario(false);
                break;
            case 2: // Registrar nuevo administrador
                registrarUsuario(true);
                break;
            case 3: // Mostrar todos los usuarios
                std::cout << "\n===== USUARIOS REGISTRADOS =====\n";
                hashUsuarios->display();
                pausa();
                break;
            case 4: // Ayuda
                abrirAyudaHTML();
                break;
            case 5: // Salir
            std::cout << "¡Hasta pronto!\n";
                return;
            case -1: // Escape presionado, lo tratamos como salir
                std::cout << "¡Hasta pronto!\n";
                return;
            default:
                std::cout << "Opción no válida.\n";
                pausa();
        }
    }
}


void MenuManager::mostrarLibrosDisponibles() {
    std::vector<Libro*> libros = arbolLibros->inOrden();
    
    // Filtrar solo libros disponibles
    std::vector<Libro*> librosDisponibles;
    for (Libro* libro : libros) {
        if (libro->getCopiasDisponibles() > 0) {
            librosDisponibles.push_back(libro);
        }
    }
    
    if (librosDisponibles.empty()) {
        std::cout << "No hay libros disponibles actualmente." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"Codigo", "Titulo", "Autor", "Genero", "Copias"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (Libro* libro : librosDisponibles) {
        std::vector<std::string> fila = {
            libro->getCodigo(),
            libro->getTitulo(),
            libro->getAutor(),
            libro->getGenero(),
            std::to_string(libro->getCopiasDisponibles())
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== LIBROS DISPONIBLES =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
}

void MenuManager::solicitarPrestamo(Usuario* usuario) {
    mostrarLibrosDisponibles();
    
    std::string codigoLibro;
    std::cout << "\nIngrese el codigo del libro que desea solicitar (o 'x' para cancelar): ";
    std::cin >> codigoLibro;
    
    if (codigoLibro == "x" || codigoLibro == "X") {
        std::cout << "Operacion cancelada.\n";
        return;
    }
    
    Libro* libro = arbolLibros->buscar(codigoLibro);
    
    if (!libro) {
        std::cout << "Error: El libro con codigo " << codigoLibro << " no existe.\n";
        return;
    }
    
    if (libro->getCopiasDisponibles() <= 0) {
        std::cout << "Error: No hay copias disponibles del libro \"" << libro->getTitulo() << "\".\n";
        return;
    }
    
    // Mostrar detalles del libro
    std::cout << "\nDetalles del libro:\n"
              << "Título: " << libro->getTitulo() << "\n"
              << "Autor: " << libro->getAutor() << "\n"
              << "Ubicación: " << libro->getUbicacion() << "\n\n";
    
    bool confirmar = mostrarMenuConfirmacion("¿Desea confirmar el prestamo?");
    
    if (confirmar) {
        if (prestamoManager->solicitarPrestamo(usuario, codigoLibro)) {
            std::cout << "Prestamo realizado con exito.\n";
            
            // Guardar los datos actualizados
            if (dbManager) {
                dbManager->guardarPrestamos();
                dbManager->guardarLibros(); 
            }
        }
    } else {
        std::cout << "Préstamo cancelado.\n";
    }
}


void MenuManager::devolverLibro(Usuario* usuario) {
    std::vector<Prestamo> prestamosActivos = 
        prestamoManager->buscarPrestamosUsuario(usuario->getIdUsuario());
    
    if (prestamosActivos.empty()) {
        std::cout << "No tiene prestamos activos para devolver." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Libro", "Fecha Devolucion"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (const Prestamo& prestamo : prestamosActivos) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            tituloLibro,
            prestamo.getFechaDevolucion()
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== PRESTAMOS ACTIVOS =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
    
    std::string idPrestamo;
    std::cout << "\nIngrese el ID del prestamo a devolver (o 'x' para cancelar): ";

    std::cin >> idPrestamo;
    
    if (idPrestamo == "x" || idPrestamo == "X") {
        std::cout << "Operacion cancelada." << std::endl;
        return;
    }
    
    // Verificar que el préstamo pertenece al usuario
    bool prestamoDelUsuario = false;
    for (const Prestamo& prestamo : prestamosActivos) {
        if (prestamo.getIdPrestamo() == idPrestamo) {
            prestamoDelUsuario = true;
            break;
        }
    }
    
    if (!prestamoDelUsuario) {
        std::cout << "Error: El prestamo no pertenece a este usuario o no esta activo." << std::endl;
        return;
    }
    bool confirmar = mostrarMenuConfirmacion("¿Desea confirmar la devolucion?");
    if (confirmar) {
        if (prestamoManager->devolverLibro(idPrestamo)) {
            std::cout << "Devolucion registrada con exito." << std::endl;
            
            // Guardar los datos actualizados
            if (dbManager) {
                dbManager->guardarPrestamos();
                dbManager->guardarLibros(); 
            }
        }
    } else {
        std::cout << "Devolucion cancelada." << std::endl;
    }
}

void MenuManager::mostrarPrestamosActivos(Usuario* usuario) {
    std::vector<Prestamo> prestamosActivos = 
        prestamoManager->buscarPrestamosUsuario(usuario->getIdUsuario());
    
    if (prestamosActivos.empty()) {
        std::cout << "No tiene prestamos activos." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Libro", "Prestamo", "Devolucion"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (const Prestamo& prestamo : prestamosActivos) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            tituloLibro,
            prestamo.getFechaPrestamo(),
            prestamo.getFechaDevolucion()
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== PRESTAMOS ACTIVOS DE " << usuario->getNombre() << " =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
}

void MenuManager::mostrarHistorialPrestamos(Usuario* usuario) {
    std::vector<Prestamo> historialUsuario = 
        prestamoManager->obtenerHistorialPrestamoUsuario(usuario->getIdUsuario());
    
    if (historialUsuario.empty()) {
        std::cout << "No hay historial de prestamos." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Libro", "Prestamo", "Devolución", "Estado"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (const Prestamo& prestamo : historialUsuario) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        std::string estadoMostrar = prestamo.getEstado();
        
        if (prestamo.getEstado() == "Devuelto") {
            estadoMostrar += (prestamo.fueDevueltoATiempo() ? " (A tiempo)" : " (Tardío)");
        } else if (prestamo.getEstado() == "Activo" && prestamo.estaVencido()) {
            estadoMostrar = "Vencido";
        }
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            tituloLibro,
            prestamo.getFechaPrestamo(),
            prestamo.getFechaDevolucion(),
            estadoMostrar
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== HISTORIAL DE PRÉSTAMOS DE " << usuario->getNombre() << " =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
}

void MenuManager::mostrarPrestamosVencidos() {
    std::vector<Prestamo> prestamosVencidos = prestamoManager->obtenerPrestamosVencidos();
    
    if (prestamosVencidos.empty()) {
        std::cout << "No hay préstamos vencidos actualmente." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Usuario", "Libro", "Devolucion", "Dias Retraso", "Multa"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    int totalMulta = 0;
    
    for (const Prestamo& prestamo : prestamosVencidos) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        int multa = prestamoManager->calcularMulta(prestamo);
        totalMulta += multa;
        
        // Calcular días de retraso
        struct std::tm tmFechaDevolucion = {};
        std::sscanf(prestamo.getFechaDevolucion().c_str(), "%d-%d-%d", 
                    &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
        tmFechaDevolucion.tm_year -= 1900;
        tmFechaDevolucion.tm_mon -= 1;
        
        std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
        std::time_t fechaActualT = std::time(nullptr);
        
        int diasRetraso = std::difftime(fechaActualT, fechaDevolucionT) / (60 * 60 * 24);
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            prestamo.getIdUsuario(),
            tituloLibro,
            prestamo.getFechaDevolucion(),
            std::to_string(diasRetraso),
            "$" + std::to_string(multa)
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== PRESTAMOS VENCIDOS =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
    
    // Mostrar el total de multas
    std::vector<std::string> totalFila(encabezados.size(), "");
    totalFila[0] = "TOTAL MULTAS PENDIENTES:";
    totalFila[encabezados.size() - 1] = "$" + std::to_string(totalMulta);
    
    imprimirFilaTabla(totalFila, anchos);
    imprimirLineaHorizontal(anchos);
}

void MenuManager::mostrarHistorialUsuarioParaAdmin(const std::string& idUsuario) {
    std::vector<Prestamo> historialUsuario = 
        prestamoManager->obtenerHistorialPrestamoUsuario(idUsuario);
    
    if (historialUsuario.empty()) {
        std::cout << "No hay historial de préstamos para el usuario con ID: " << idUsuario << std::endl;
        return;
    }
    
    // Intentar obtener el nombre del usuario
    Usuario* usuario = hashUsuarios->find(idUsuario);
    std::string nombreUsuario = usuario ? usuario->getNombre() : idUsuario;
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Libro", "Prestamo", "Devolucion", "Estado"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (const Prestamo& prestamo : historialUsuario) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        std::string estadoMostrar = prestamo.getEstado();
        
        if (prestamo.getEstado() == "Devuelto") {
            estadoMostrar += (prestamo.fueDevueltoATiempo() ? " (A tiempo)" : " (Tardío)");
        } else if (prestamo.getEstado() == "Activo" && prestamo.estaVencido()) {
            estadoMostrar = "Vencido";
        }
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            tituloLibro,
            prestamo.getFechaPrestamo(),
            prestamo.getFechaDevolucion(),
            estadoMostrar
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== HISTORIAL DE PRESTAMOS DEL USUARIO " << nombreUsuario << " (" << idUsuario << ") =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
}

void MenuManager::verMultasUsuario(Usuario* usuario) {
    std::vector<Prestamo> prestamosUsuario = 
        prestamoManager->buscarPrestamosUsuario(usuario->getIdUsuario());
    
    if (prestamosUsuario.empty()) {
        std::cout << "No tiene prestamos activos." << std::endl;
        return;
    }
    
    // Filtrar solo préstamos vencidos
    std::vector<Prestamo> prestamosVencidos;
    for (const Prestamo& prestamo : prestamosUsuario) {
        if (prestamo.estaVencido()) {
            prestamosVencidos.push_back(prestamo);
        }
    }
    
    if (prestamosVencidos.empty()) {
        std::cout << "\n===== MULTAS DE " << usuario->getNombre() << " =====\n";
        std::cout << "No tiene multas pendientes actualmente.\n";
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Libro", "Dias Retraso", "Multa", "Estado"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    int totalMulta = 0;
    
    for (const Prestamo& prestamo : prestamosVencidos) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        if (libro) {
            int multa = prestamoManager->calcularMulta(prestamo);
            totalMulta += multa;
            
            // Calcular días de retraso
            struct std::tm tmFechaDevolucion = {};
            std::sscanf(prestamo.getFechaDevolucion().c_str(), "%d-%d-%d", 
                        &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
            tmFechaDevolucion.tm_year -= 1900;
            tmFechaDevolucion.tm_mon -= 1;
            
            std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
            std::time_t fechaActualT = std::time(nullptr);
            
            int diasRetraso = std::difftime(fechaActualT, fechaDevolucionT) / (60 * 60 * 24);
            
            std::vector<std::string> fila = {
                prestamo.getIdPrestamo(),
                libro->getTitulo(),
                std::to_string(diasRetraso),
                "$" + std::to_string(multa),
                "Vencido"
            };
            
            datos.push_back(fila);
        }
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== MULTAS DE " << usuario->getNombre() << " =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
    
    // Mostrar el total de multas
    std::vector<std::string> totalFila(encabezados.size(), "");
    totalFila[0] = "TOTAL MULTAS:";
    totalFila[3] = "$" + std::to_string(totalMulta);
    
    imprimirFilaTabla(totalFila, anchos);
    imprimirLineaHorizontal(anchos);
}

void MenuManager::generarReporteGeneral() {
    std::vector<Prestamo> todosLosPrestamos = prestamoManager->obtenerTodosLosPrestamos();
    
    if (todosLosPrestamos.empty()) {
        std::cout << "No hay prestamos registrados en el sistema para generar reportes." << std::endl;
        return;
    }
    
    int totalPrestamos = todosLosPrestamos.size();
    int prestamosActivos = 0;
    int prestamosDevueltos = 0;
    int prestamosATiempo = 0;
    int prestamosTardios = 0;
    int prestamosVencidos = 0;
    
    for (const Prestamo& prestamo : todosLosPrestamos) {
        if (prestamo.getEstado() == "Activo") {
            prestamosActivos++;
            if (prestamo.estaVencido()) {
                prestamosVencidos++;
            }
        } else if (prestamo.getEstado() == "Devuelto") {
            prestamosDevueltos++;
            if (prestamo.fueDevueltoATiempo()) {
                prestamosATiempo++;
            } else {
                prestamosTardios++;
            }
        }
    }
    
    // Definir encabezados y datos para la tabla de estadísticas
    std::vector<std::string> encabezados = {"Estadistica", "Valor", "Porcentaje"};
    std::vector<std::vector<std::string>> datos;
    
    // Calcular porcentajes
    double porcentajeActivos = totalPrestamos > 0 ? (static_cast<double>(prestamosActivos) / totalPrestamos) * 100 : 0;
    double porcentajeVencidos = prestamosActivos > 0 ? (static_cast<double>(prestamosVencidos) / prestamosActivos) * 100 : 0;
    double porcentajeDevueltos = totalPrestamos > 0 ? (static_cast<double>(prestamosDevueltos) / totalPrestamos) * 100 : 0;
    double porcentajeATiempo = prestamosDevueltos > 0 ? (static_cast<double>(prestamosATiempo) / prestamosDevueltos) * 100 : 0;
    double porcentajeTardios = prestamosDevueltos > 0 ? (static_cast<double>(prestamosTardios) / prestamosDevueltos) * 100 : 0;
    
    // Añadir las filas de datos
    datos.push_back({"Total de préstamos", std::to_string(totalPrestamos), "100.00%"});
    datos.push_back({"Préstamos activos", std::to_string(prestamosActivos), 
                    std::to_string(static_cast<int>(porcentajeActivos)) + "." + 
                    std::to_string(static_cast<int>(porcentajeActivos * 100) % 100) + "%"});
    datos.push_back({"Préstamos vencidos", std::to_string(prestamosVencidos), 
                    std::to_string(static_cast<int>(porcentajeVencidos)) + "." + 
                    std::to_string(static_cast<int>(porcentajeVencidos * 100) % 100) + "%"});
    datos.push_back({"Préstamos devueltos", std::to_string(prestamosDevueltos), 
                    std::to_string(static_cast<int>(porcentajeDevueltos)) + "." + 
                    std::to_string(static_cast<int>(porcentajeDevueltos * 100) % 100) + "%"});
    datos.push_back({"Devueltos a tiempo", std::to_string(prestamosATiempo), 
                    std::to_string(static_cast<int>(porcentajeATiempo)) + "." + 
                    std::to_string(static_cast<int>(porcentajeATiempo * 100) % 100) + "%"});
    datos.push_back({"Devueltos con retraso", std::to_string(prestamosTardios), 
                    std::to_string(static_cast<int>(porcentajeTardios)) + "." + 
                    std::to_string(static_cast<int>(porcentajeTardios * 100) % 100) + "%"});
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla de estadísticas
    std::cout << "\n===== REPORTE GENERAL DEL SISTEMA =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
    
    // Obtener multas pendientes
    std::vector<Prestamo> prestamosVencidosLista = prestamoManager->obtenerPrestamosVencidos();
    int totalMultas = 0;
    
    for (const Prestamo& prestamo : prestamosVencidosLista) {
        totalMultas += prestamoManager->calcularMulta(prestamo);
    }
    
    // Mostrar información de multas
    std::cout << "\n--- Información de Multas ---\n";
    std::cout << "Prestamos actualmente vencidos: " << prestamosVencidosLista.size() << std::endl;
    std::cout << "Total de multas pendientes: $" << totalMultas << std::endl;
    
    // Si hay préstamos vencidos, mostrar detalles
    if (!prestamosVencidosLista.empty()) {
        std::vector<std::string> encabezadosMultas = {"ID Prestamo", "Usuario", "Libro", "Dias Retraso", "Multa"};
        std::vector<std::vector<std::string>> datosMultas;
        
        for (const Prestamo& prestamo : prestamosVencidosLista) {
            Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
            std::string tituloLibro;
            
            if (libro) {
                tituloLibro = libro->getTitulo();
            } else {
                tituloLibro = prestamo.getIdLibro() + " (eliminado)";
            }
            
            // Calcular días de retraso
            struct std::tm tmFechaDevolucion = {};
            std::sscanf(prestamo.getFechaDevolucion().c_str(), "%d-%d-%d", 
                      &tmFechaDevolucion.tm_year, &tmFechaDevolucion.tm_mon, &tmFechaDevolucion.tm_mday);
            tmFechaDevolucion.tm_year -= 1900;
            tmFechaDevolucion.tm_mon -= 1;
            
            std::time_t fechaDevolucionT = std::mktime(&tmFechaDevolucion);
            std::time_t fechaActualT = std::time(nullptr);
            
            int diasRetraso = std::difftime(fechaActualT, fechaDevolucionT) / (60 * 60 * 24);
            int multa = prestamoManager->calcularMulta(prestamo);
            
            datosMultas.push_back({
                prestamo.getIdPrestamo(),
                prestamo.getIdUsuario(),
                tituloLibro,
                std::to_string(diasRetraso),
                "$" + std::to_string(multa)
            });
        }
        
        std::vector<int> anchosMultas = calcularAnchosColumnas(datosMultas, encabezadosMultas);
        
        std::cout << "\n--- Detalle de Prestamos Vencidos ---\n";
        
        imprimirLineaHorizontal(anchosMultas);
        imprimirFilaTabla(encabezadosMultas, anchosMultas);
        imprimirLineaHorizontal(anchosMultas);
        
        for (const auto& fila : datosMultas) {
            imprimirFilaTabla(fila, anchosMultas);
        }
        
        imprimirLineaHorizontal(anchosMultas);
    }
}

void MenuManager::mostrarTodosLosPrestamos() {
    std::vector<Prestamo> todosLosPrestamos = prestamoManager->obtenerTodosLosPrestamos();
    
    if (todosLosPrestamos.empty()) {
        std::cout << "No hay prestamos registrados en el sistema." << std::endl;
        return;
    }
    
    // Definir encabezados
    std::vector<std::string> encabezados = {"ID Prestamo", "Usuario", "Libro", "Prestamo", "Devolucion", "Estado"};
    
    // Preparar datos para la tabla
    std::vector<std::vector<std::string>> datos;
    
    for (const Prestamo& prestamo : todosLosPrestamos) {
        Libro* libro = arbolLibros->buscar(prestamo.getIdLibro());
        std::string tituloLibro;
        
        // Verificar si el libro existe aún en el sistema
        if (libro) {
            tituloLibro = libro->getTitulo();
        } else {
            // Si el libro ya no existe, mostrar su ID con una nota
            tituloLibro = prestamo.getIdLibro() + " (eliminado)";
        }
        
        std::string estadoMostrar = prestamo.getEstado();
        
        if (prestamo.getEstado() == "Devuelto") {
            estadoMostrar += (prestamo.fueDevueltoATiempo() ? " (A tiempo)" : " (Tardío)");
        } else if (prestamo.getEstado() == "Activo" && prestamo.estaVencido()) {
            estadoMostrar = "Vencido";
        }
        
        std::vector<std::string> fila = {
            prestamo.getIdPrestamo(),
            prestamo.getIdUsuario(),
            tituloLibro,
            prestamo.getFechaPrestamo(),
            prestamo.getFechaDevolucion(),
            estadoMostrar
        };
        
        datos.push_back(fila);
    }
    
    // Calcular anchos óptimos para cada columna
    std::vector<int> anchos = calcularAnchosColumnas(datos, encabezados);
    
    // Imprimir la tabla
    std::cout << "\n===== TODOS LOS PRESTAMOS =====\n";
    
    imprimirLineaHorizontal(anchos);
    imprimirFilaTabla(encabezados, anchos);
    imprimirLineaHorizontal(anchos);
    
    for (const auto& fila : datos) {
        imprimirFilaTabla(fila, anchos);
    }
    
    imprimirLineaHorizontal(anchos);
}

void MenuManager::setDatabaseManager(DatabaseManager* dbManager) {
    this->dbManager = dbManager;
}



// Función para imprimir una línea horizontal de la tabla
void MenuManager::imprimirLineaHorizontal(const std::vector<int>& anchos) const {
    std::cout << "+";
    for (int ancho : anchos) {
        std::cout << std::string(ancho + 2, '-') << "+";
    }
    std::cout << "\n";
}

// Función para imprimir una fila de la tabla
void MenuManager::imprimirFilaTabla(const std::vector<std::string>& datos, const std::vector<int>& anchos) const {
    std::cout << "| ";
    for (size_t i = 0; i < datos.size(); ++i) {
        std::cout << std::left << std::setw(anchos[i]) << datos[i] << " | ";
    }
    std::cout << "\n";
}

// Función para calcular el ancho óptimo de cada columna
std::vector<int> MenuManager::calcularAnchosColumnas(const std::vector<std::vector<std::string>>& datos, const std::vector<std::string>& encabezados) const {
    std::vector<int> anchos(encabezados.size(), 0);
    
    // Considerar el ancho de los encabezados
    for (size_t i = 0; i < encabezados.size(); ++i) {
        anchos[i] = encabezados[i].length();
    }
    
    // Considerar el ancho de los datos
    for (const auto& fila : datos) {
        for (size_t i = 0; i < fila.size() && i < anchos.size(); ++i) {
            anchos[i] = std::max(anchos[i], static_cast<int>(fila[i].length()));
        }
    }
    
    return anchos;
}

// Añade estas implementaciones en MenuManager.cpp:

// Función para mover el cursor a una posición específica
void MenuManager::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Función general para mostrar un menú dinámico
int MenuManager::mostrarMenuDinamico(const std::string& titulo, const std::vector<std::string>& opciones, int posX, int posY) {
    int opcionSeleccionada = 0;
    bool salir = false;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    while (!salir) {
        system("cls"); // Limpiar pantalla
        
        // Determinar el ancho del menú según la opción más larga
        size_t anchoMenu = titulo.length() + 10;
        for (const auto& opcion : opciones) {
            anchoMenu = std::max(anchoMenu, opcion.length() + 6);
        }

        // Dibujar el borde superior
        gotoxy(posX, posY);
        std::cout << "+" << std::string(anchoMenu, '-') << "+";

        // Título centrado
        gotoxy(posX, posY + 1);
        std::cout << "| " << std::setw((anchoMenu - titulo.length()) / 2 + titulo.length()) << std::left << titulo << " |";

        // Línea separadora
        gotoxy(posX, posY + 2);
        std::cout << "+" << std::string(anchoMenu, '-') << "+";

        // Dibujar opciones
        for (size_t i = 0; i < opciones.size(); i++) {
            gotoxy(posX, posY + 3 + i);
            if (i == opcionSeleccionada) {
                SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                std::cout << "| > " << std::setw(anchoMenu - 4) << std::left << opciones[i] << " |";
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            } else {
                std::cout << "|   " << std::setw(anchoMenu - 4) << std::left << opciones[i] << " |";
            }
        }

        // Dibujar borde inferior
        gotoxy(posX, posY + 3 + opciones.size());
        std::cout << "+" << std::string(anchoMenu, '-') << "+";

        // Instrucciones
        gotoxy(posX, posY + 5 + opciones.size());
        std::cout << "use las flechas arriba y abajo para moverse, Enter para seleccionar, Esc para salir";
        std::cout << std::endl;

        // Capturar entrada del usuario
        int tecla = _getch();
        if (tecla == 224) {
            tecla = _getch();
            if (tecla == 72) opcionSeleccionada = (opcionSeleccionada > 0) ? opcionSeleccionada - 1 : opciones.size() - 1; // Flecha arriba
            else if (tecla == 80) opcionSeleccionada = (opcionSeleccionada < opciones.size() - 1) ? opcionSeleccionada + 1 : 0; // Flecha abajo
        } else if (tecla == 13) { // Enter
            salir = true;
        } else if (tecla == 27) { // Escape
            return -1;
        }
    }
    
    return opcionSeleccionada;
}



bool MenuManager::mostrarMenuConfirmacion(const std::string& titulo) {
    std::vector<std::string> opciones = {"Si", "No"};
    int resultado = mostrarMenuDinamico(titulo, opciones);
    return resultado == 0;
}

std::string MenuManager::mostrarMenuBackups(const std::vector<std::string>& backups) {
    if (backups.empty()) {
        std::cout << "No hay backups disponibles." << std::endl;
        return "";
    }

    std::vector<std::string> opcionesBackup;
    for (const auto& backup : backups) {
        // Formatear el nombre del backup manualmente
        size_t ultimaBarra = backup.find_last_of("/\\");
        std::string nombreArchivo;
        if (ultimaBarra != std::string::npos) {
            nombreArchivo = backup.substr(ultimaBarra + 1);
        } else {
            nombreArchivo = backup;
        }
        
        // Extraer la fecha del nombre (formato esperado: YYYYMMDD.txt)
        if (nombreArchivo.length() >= 12 && nombreArchivo.substr(nombreArchivo.length() - 4) == ".txt") {
            std::string fechaStr = nombreArchivo.substr(0, 8);
            
            // Formatear como DD/MM/YYYY
            std::string dia = fechaStr.substr(6, 2);
            std::string mes = fechaStr.substr(4, 2);
            std::string anio = fechaStr.substr(0, 4);
            
            opcionesBackup.push_back("Backup del " + dia + "/" + mes + "/" + anio);
        } else {
            opcionesBackup.push_back(nombreArchivo);
        }
    }

    int seleccion = mostrarMenuDinamico("===== SELECCIONAR BACKUP =====", opcionesBackup);
    
    // Si se cancela la selección
    if (seleccion == -1) {
        return "";
    }

    // Devolver el backup seleccionado
    return backups[seleccion];
}

void MenuManager::abrirAyudaHTML() {
    // Nombre del archivo HTML de ayuda (debe estar en el mismo directorio que el ejecutable)
    std::string rutaManual = "ayuda_biblioteca.html";
    
    std::cout << "\nAbriendo manual de ayuda en el navegador...\n";
    
    // Abrir el archivo HTML con el navegador predeterminado
    #ifdef _WIN32
        system(("start " + rutaManual).c_str());
    #elif __APPLE__
        system(("open " + rutaManual).c_str());
    #else
        system(("xdg-open " + rutaManual).c_str());
    #endif
    
    // Pequeña pausa para mostrar el mensaje
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
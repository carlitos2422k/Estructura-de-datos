#include "RecomendacionManager.h"
#include <iostream>
#include <cmath>
#include <random>

RecomendacionManager::RecomendacionManager(PrestamoManager* prestamoManager, ArbolAVL* arbolLibros, HashUsuario* hashUsuarios)
    : prestamoManager(prestamoManager), arbolLibros(arbolLibros), hashUsuarios(hashUsuarios) {
    
    // Valores predeterminados para los pesos
    pesoHistorialPersonal = 0.4;
    pesoPopularidad = 0.3;
    pesoRelacionGeneros = 0.2;
    pesoNovedades = 0.1;
    maxRecomendaciones = 5;
}

void RecomendacionManager::configurarParametros(double pesoHistorial, double pesoPopularidad, 
                                              double pesoRelacion, double pesoNovedades, int maxRecom) {
    // Validar que los pesos sumen 1.0
    double sumaTotal = pesoHistorial + pesoPopularidad + pesoRelacion + pesoNovedades;
    if (std::abs(sumaTotal - 1.0) > 0.01) {
        std::cout << "Advertencia: Los pesos no suman 1.0. Se ajustaran automaticamente." << std::endl;
        
        // Normalizar los pesos
        pesoHistorialPersonal = pesoHistorial / sumaTotal;
        pesoPopularidad = pesoPopularidad / sumaTotal;
        pesoRelacionGeneros = pesoRelacion / sumaTotal;
        pesoNovedades = pesoNovedades / sumaTotal;
    } else {
        pesoHistorialPersonal = pesoHistorial;
        pesoPopularidad = pesoPopularidad;
        pesoRelacionGeneros = pesoRelacion;
        pesoNovedades = pesoNovedades;
    }
    
    maxRecomendaciones = maxRecom > 0 ? maxRecom : 5;
}

void RecomendacionManager::inicializar() {
    // Limpiar los mapas existentes
    perfilesUsuarios.clear();
    relacionGeneros.clear();
    popularidadLibros.clear();
    
    // Analizar el historial de préstamos para crear los perfiles
    analizarHistorialPrestamos();
    
    // Calcular relaciones entre géneros
    calcularRelacionesGeneros();
    
    // Calcular popularidad de los libros
    calcularPopularidadLibros();
}

void RecomendacionManager::analizarHistorialPrestamos() {
    // Obtener todos los préstamos del sistema
    std::vector<Prestamo> todosPrestamos = prestamoManager->obtenerTodosLosPrestamos();
    
    for (const Prestamo& prestamo : todosPrestamos) {
        std::string idUsuario = prestamo.getIdUsuario();
        std::string idLibro = prestamo.getIdLibro();
        
        // Buscar el libro en el árbol AVL
        Libro* libro = arbolLibros->buscar(idLibro);
        if (libro) {
            // Incrementar contador de popularidad del libro
            popularidadLibros[idLibro]++;
            
            // Obtener el género del libro y actualizar perfil del usuario
            std::string genero = libro->getGenero();
            if (!genero.empty()) {
                perfilesUsuarios[idUsuario][genero]++;
            }
        }
    }
}

void RecomendacionManager::calcularRelacionesGeneros() {
    // Para cada usuario, analizar qué géneros tomó prestados juntos
    for (const auto& [idUsuario, generos] : perfilesUsuarios) {
        // Para cada par de géneros que el usuario ha tomado prestado
        for (const auto& [genero1, frec1] : generos) {
            for (const auto& [genero2, frec2] : generos) {
                if (genero1 != genero2) {
                    // Aumentar la relación entre estos géneros
                    // La fuerza de la relación es proporcional a la frecuencia de ambos géneros
                    double relacionFuerza = std::min(frec1, frec2) / 
                                          (double)std::max(1, std::max(frec1, frec2));
                    
                    relacionGeneros[genero1][genero2] += relacionFuerza;
                }
            }
        }
    }
    
    // Normalizar las relaciones
    for (auto& [genero, relaciones] : relacionGeneros) {
        double maxRelacion = 0.0;
        
        // Encontrar el valor máximo
        for (const auto& [_, valor] : relaciones) {
            maxRelacion = std::max(maxRelacion, valor);
        }
        
        // Normalizar los valores si hay un máximo
        if (maxRelacion > 0) {
            for (auto& [generoRelacionado, valor] : relaciones) {
                valor /= maxRelacion;
            }
        }
    }
}

void RecomendacionManager::calcularPopularidadLibros() {
    // Ya calculamos la popularidad en analizarHistorialPrestamos
    // Aquí podríamos hacer algún procesamiento adicional si fuera necesario
    
    // Por ejemplo, podríamos normalizar las popularidades
    int maxPopularidad = 0;
    
    for (const auto& [_, popularidad] : popularidadLibros) {
        maxPopularidad = std::max(maxPopularidad, popularidad);
    }
    
    // No es necesario normalizar para el cálculo de puntuación, pero podría ser útil
    // para mostrar la información de manera más legible
}

bool RecomendacionManager::libroYaPrestado(const std::string& idUsuario, const std::string& codigoLibro) {
    std::vector<Prestamo> historialUsuario = 
        prestamoManager->obtenerHistorialPrestamoUsuario(idUsuario);
    
    for (const Prestamo& prestamo : historialUsuario) {
        if (prestamo.getIdLibro() == codigoLibro) {
            return true;
        }
    }
    
    return false;
}

double RecomendacionManager::calcularPuntuacionLibro(const std::string& idUsuario, Libro* libro, std::vector<std::string>& razones) {
    if (!libro) return 0.0;
    
    double puntuacion = 0.0;
    razones.clear();
    
    // 1. Factor de historial personal (qué tanto coincide con los géneros que ha leído)
    double factorHistorial = 0.0;
    if (perfilesUsuarios.count(idUsuario)) {
        const std::map<std::string, int>& generosUsuario = perfilesUsuarios[idUsuario];
        std::string generoLibro = libro->getGenero();
        
        // Si el usuario ha leído de este género antes
        if (generosUsuario.count(generoLibro)) {
            int frecuenciaGenero = generosUsuario.at(generoLibro);
            int totalPrestamos = 0;
            
            for (const auto& [_, frec] : generosUsuario) {
                totalPrestamos += frec;
            }
            
            factorHistorial = static_cast<double>(frecuenciaGenero) / totalPrestamos;
            std::string razon = "Coincide con tu interes en el genero " + generoLibro;
            razones.push_back(razon);
        }
    }
    
    // 2. Factor de popularidad (qué tan popular es el libro entre otros usuarios)
    double factorPopularidad = 0.0;
    if (popularidadLibros.count(libro->getCodigo())) {
        int popularidad = popularidadLibros[libro->getCodigo()];
        int maxPopularidad = 0;
        
        for (const auto& [_, pop] : popularidadLibros) {
            maxPopularidad = std::max(maxPopularidad, pop);
        }
        
        if (maxPopularidad > 0) {
            factorPopularidad = static_cast<double>(popularidad) / maxPopularidad;
            if (factorPopularidad > 0.7) {
                razones.push_back("Popular entre otros lectores");
            }
        }
    }
    
    // 3. Factor de relación de géneros (qué tanto se relaciona con otros géneros que le gustan)
    double factorRelacion = 0.0;
    if (perfilesUsuarios.count(idUsuario)) {
        const std::map<std::string, int>& generosUsuario = perfilesUsuarios[idUsuario];
        std::string generoLibro = libro->getGenero();
        
        if (relacionGeneros.count(generoLibro)) {
            const std::map<std::string, double>& generosRelacionados = relacionGeneros[generoLibro];
            
            double sumaPonderada = 0.0;
            double sumaRelaciones = 0.0;
            
            for (const auto& [generoRelacionado, fuerzaRelacion] : generosRelacionados) {
                // Si el usuario tiene interés en este género relacionado
                if (generosUsuario.count(generoRelacionado)) {
                    int frecuenciaGenero = generosUsuario.at(generoRelacionado);
                    sumaPonderada += fuerzaRelacion * frecuenciaGenero;
                    sumaRelaciones += fuerzaRelacion;
                }
            }
            
            if (sumaRelaciones > 0) {
                factorRelacion = sumaPonderada / sumaRelaciones;
                
                // Encontrar el género relacionado más fuerte para mostrar en razones
                std::string generoMasRelacionado;
                double maxRelacion = 0.0;
                
                for (const auto& [generoRelacionado, fuerzaRelacion] : generosRelacionados) {
                    if (generosUsuario.count(generoRelacionado) && fuerzaRelacion > maxRelacion) {
                        maxRelacion = fuerzaRelacion;
                        generoMasRelacionado = generoRelacionado;
                    }
                }
                
                if (!generoMasRelacionado.empty()) {
                    std::string razon = "Similar a tu interes en " + generoMasRelacionado;
                    razones.push_back(razon);
                }
            }
        }
    }
    
    // 4. Factor de novedad (si el usuario no ha leído el libro)
    double factorNovedad = 0.0;
    if (!libroYaPrestado(idUsuario, libro->getCodigo())) {
        factorNovedad = 1.0;
        razones.push_back("Nuevo para ti");
    }
    
    // Calcular puntuación ponderada
    puntuacion = (pesoHistorialPersonal * factorHistorial) +
                (pesoPopularidad * factorPopularidad) +
                (pesoRelacionGeneros * factorRelacion) +
                (pesoNovedades * factorNovedad);
    
    return puntuacion;
}



std::vector<Recomendacion> RecomendacionManager::generarRecomendaciones(const std::string& idUsuario, int cantidad) {
    // Verificar si el usuario existe
    if (!hashUsuarios->find(idUsuario)) {
        std::cout << "Error: Usuario no encontrado." << std::endl;
        return std::vector<Recomendacion>();
    }
    
    // Obtener todos los libros disponibles como candidatos
    std::vector<Libro*> librosDisponibles = arbolLibros->inOrden();
    
    // Filtrar solo libros con copias disponibles
    std::vector<Libro*> candidatos;
    for (Libro* libro : librosDisponibles) {
        if (libro->getCopiasDisponibles() > 0) {
            candidatos.push_back(libro);
        }
    }
    
    // Si no hay suficientes candidatos, devolver los que hay
    if (static_cast<int>(candidatos.size()) <= cantidad) {
        std::vector<Recomendacion> recomendaciones;
        for (Libro* libro : candidatos) {
            std::vector<std::string> razones;
            double puntuacion = calcularPuntuacionLibro(idUsuario, libro, razones);
            Recomendacion rec(libro, puntuacion);
            rec.razones = razones;
            recomendaciones.push_back(rec);
        }
        
        // Ordenar por puntuación
        std::sort(recomendaciones.begin(), recomendaciones.end());
        return recomendaciones;
    }
    
    // Pre-calcular las puntuaciones para cada libro para reducir cálculos repetidos
    std::map<std::string, std::pair<double, std::vector<std::string>>> puntuacionesPrecalculadas;
    for (Libro* libro : candidatos) {
        std::vector<std::string> razones;
        double puntuacion = calcularPuntuacionLibro(idUsuario, libro, razones);
        puntuacionesPrecalculadas[libro->getCodigo()] = std::make_pair(puntuacion, razones);
    }
    
    // Ordenar los candidatos por puntuación para explorar primero los más prometedores
    std::sort(candidatos.begin(), candidatos.end(), 
        [&puntuacionesPrecalculadas](Libro* a, Libro* b) {
            return puntuacionesPrecalculadas[a->getCodigo()].first > 
                   puntuacionesPrecalculadas[b->getCodigo()].first;
        });
    
    // Limitar el número de candidatos para reducir el espacio de búsqueda
    const int MAX_CANDIDATOS = std::min(20, static_cast<int>(candidatos.size()));
    if (static_cast<int>(candidatos.size()) > MAX_CANDIDATOS) {
        candidatos.resize(MAX_CANDIDATOS);
    }
    
    // Variables para el backtracking
    std::vector<Recomendacion> recomendacionesActuales;
    std::vector<Recomendacion> mejoresRecomendaciones;
    std::set<std::string> librosConsiderados;
    double mejorPuntuacion = 0.0;
    
    std::cout << "Ejecutando algoritmo de backtracking para encontrar la mejor combinacion..." << std::endl;
    
    // Iniciar el algoritmo de backtracking
    auto startTime = std::chrono::high_resolution_clock::now();
    
    backtrackRecomendaciones(
        idUsuario,
        recomendacionesActuales,
        mejoresRecomendaciones,
        librosConsiderados,
        candidatos,
        0,
        0.0,
        mejorPuntuacion
    );
    
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    
    std::cout << "Tiempo de ejecucion del backtracking: " << duration << " ms" << std::endl;
    
    // Si no encontramos recomendaciones con backtracking, usar enfoque directo
    if (mejoresRecomendaciones.empty()) {
        std::cout << "No se encontraron combinaciones optimas con backtracking, usando enfoque directo." << std::endl;
        std::vector<Recomendacion> directRecomendaciones;
        
        for (Libro* libro : candidatos) {
            std::vector<std::string> razones = puntuacionesPrecalculadas[libro->getCodigo()].second;
            double puntuacion = puntuacionesPrecalculadas[libro->getCodigo()].first;
            
            Recomendacion rec(libro, puntuacion);
            rec.razones = razones;
            directRecomendaciones.push_back(rec);
        }
        
        // Ordenar por puntuación
        std::sort(directRecomendaciones.begin(), directRecomendaciones.end());
        
        // Limitar la cantidad de recomendaciones
        if (static_cast<int>(directRecomendaciones.size()) > cantidad) {
            std::vector<Recomendacion> limitedRecomendaciones;
            for (int i = 0; i < cantidad && i < static_cast<int>(directRecomendaciones.size()); i++) {
                limitedRecomendaciones.push_back(directRecomendaciones[i]);
            }
            return limitedRecomendaciones;
        }
        
        return directRecomendaciones;
    }
    
    // Limitar la cantidad de recomendaciones si es necesario
    if (static_cast<int>(mejoresRecomendaciones.size()) > cantidad) {
        std::vector<Recomendacion> recomendacionesLimitadas;
        for (int i = 0; i < cantidad && i < static_cast<int>(mejoresRecomendaciones.size()); i++) {
            recomendacionesLimitadas.push_back(mejoresRecomendaciones[i]);
        }
        return recomendacionesLimitadas;
    }
    
    return mejoresRecomendaciones;
}

void RecomendacionManager::backtrackRecomendaciones(
    const std::string& idUsuario,
    std::vector<Recomendacion>& recomendacionesActuales,
    std::vector<Recomendacion>& mejoresRecomendaciones,
    std::set<std::string>& librosConsiderados,
    std::vector<Libro*>& candidatos,
    int nivel,
    double puntuacionActual,
    double& mejorPuntuacion) {
    
    // Agregar un límite de tiempo para evitar que el algoritmo se ejecute demasiado tiempo
    static auto startTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    
    const int MAX_EXECUTION_TIME_MS = 1000; // Máximo 1 segundo
    if (duration > MAX_EXECUTION_TIME_MS) {
        // Si alcanzamos el límite de tiempo, usamos lo mejor que tenemos hasta ahora
        if (puntuacionActual > mejorPuntuacion) {
            mejorPuntuacion = puntuacionActual;
            mejoresRecomendaciones = recomendacionesActuales;
        }
        return;
    }
    
    // Limitar la profundidad para evitar una explosión combinatoria
    const int MAX_DEPTH = 5;
    if (nivel >= MAX_DEPTH) {
        if (puntuacionActual > mejorPuntuacion) {
            mejorPuntuacion = puntuacionActual;
            mejoresRecomendaciones = recomendacionesActuales;
        }
        return;
    }
    
    // Caso base: hemos alcanzado el número máximo de recomendaciones o no hay más candidatos
    if (nivel >= maxRecomendaciones || nivel >= static_cast<int>(candidatos.size())) {
        // Si esta combinación es mejor que la mejor encontrada hasta ahora, la guardamos
        if (puntuacionActual > mejorPuntuacion) {
            mejorPuntuacion = puntuacionActual;
            mejoresRecomendaciones = recomendacionesActuales;
        }
        return;
    }
    
    // Para cada candidato restante
    for (size_t i = 0; i < candidatos.size(); i++) {
        Libro* libro = candidatos[i];
        
        // Si ya hemos considerado este libro, saltar
        if (librosConsiderados.count(libro->getCodigo())) {
            continue;
        }
        
        // Calcular la puntuación de este libro
        std::vector<std::string> razones;
        double puntuacion = calcularPuntuacionLibro(idUsuario, libro, razones);
        
        // Poda: si la puntuación es demasiado baja, podemos saltarnos este candidato
        const double MIN_SCORE_THRESHOLD = 0.1;
        if (puntuacion < MIN_SCORE_THRESHOLD) {
            continue;
        }
        
        // Marcar como considerado
        librosConsiderados.insert(libro->getCodigo());
        
        // Añadir a las recomendaciones actuales
        Recomendacion rec(libro, puntuacion);
        rec.razones = razones;
        recomendacionesActuales.push_back(rec);
        
        // Recursión: intentar con el siguiente nivel
        backtrackRecomendaciones(
            idUsuario,
            recomendacionesActuales,
            mejoresRecomendaciones,
            librosConsiderados,
            candidatos,
            nivel + 1,
            puntuacionActual + puntuacion,
            mejorPuntuacion
        );
        
        // Backtracking: deshacer cambios
        recomendacionesActuales.pop_back();
        librosConsiderados.erase(libro->getCodigo());
    }
}

void RecomendacionManager::mostrarPerfilUsuario(const std::string& idUsuario) {
    if (!hashUsuarios->find(idUsuario)) {
        std::cout << "Error: Usuario no encontrado." << std::endl;
        return;
    }
    
    std::cout << "Perfil de genero para el usuario " << idUsuario << ":" << std::endl;
    
    if (perfilesUsuarios.count(idUsuario)) {
        const std::map<std::string, int>& generosUsuario = perfilesUsuarios[idUsuario];
        
        if (generosUsuario.empty()) {
            std::cout << "  Este usuario no tiene prestamos registrados." << std::endl;
            return;
        }
        
        int totalPrestamos = 0;
        for (const auto& [_, frec] : generosUsuario) {
            totalPrestamos += frec;
        }
        
        std::cout << "  Total de prestamos: " << totalPrestamos << std::endl;
        
        for (const auto& [genero, frec] : generosUsuario) {
            double porcentaje = (static_cast<double>(frec) / totalPrestamos) * 100.0;
            std::cout << "  " << genero << ": " << frec << " prestamos (" 
                    << std::fixed << std::setprecision(1) << porcentaje << "%)" << std::endl;
        }
    } else {
        std::cout << "  Este usuario no tiene prestamos registrados." << std::endl;
    }
}


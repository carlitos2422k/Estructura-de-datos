#include "JuegoLetras.h"

JuegoLetras::JuegoLetras(int w, int h) : ancho(w), alto(h), juegoTerminado(false), letraCayendo(false), coordenadaY(0) {
    // La lista se inicializa automaticamente
}

JuegoLetras::~JuegoLetras() {
    // La lista se limpia automaticamente en su destructor
}

char JuegoLetras::obtenerCelda(int x, int y) const {
    // Buscar la celda en la lista
    for (int i = 0; i < cuadricula.obtenerTamano(); i++) {
        const Celda& celda = cuadricula.obtener(i);
        if (celda.obtenerPosicion().obtenerX() == x && celda.obtenerPosicion().obtenerY() == y) {
            return celda.obtenerLetra();
        }
    }
    
    // Si no se encuentra, devolver espacio en blanco
    return ' ';
}

void JuegoLetras::establecerCelda(int x, int y, char valor) {
    // Primero verificamos si la celda ya existe
    for (int i = 0; i < cuadricula.obtenerTamano(); i++) {
        Celda& celda = cuadricula.obtener(i);
        if (celda.obtenerPosicion().obtenerX() == x && celda.obtenerPosicion().obtenerY() == y) {
            // Si existe, actualizar su valor
            if (valor == ' ') {
                // Si el nuevo valor es espacio, eliminar la celda
                cuadricula.eliminar(i);
            } else {
                celda.establecerLetra(valor);
            }
            return;
        }
    }
    
    // Si llegamos aqui, la celda no existe
    if (valor != ' ') {
        // Solo anadir si no es un espacio en blanco
        cuadricula.agregarAlFinal(Celda(valor, Punto(x, y)));
    }
}

void JuegoLetras::limpiarCelda(int x, int y) {
    establecerCelda(x, y, ' ');
}

bool JuegoLetras::esCeldaVacia(int x, int y) const {
    return obtenerCelda(x, y) == ' ';
}

void JuegoLetras::inicializar() {
    // Establecer la semilla para numeros aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Limpiar el grid (la lista ya estara vacia, pero por si acaso)
    cuadricula.limpiar();
    
    // Generar la primera letra
    generarLetraAleatoria();
    
    // Colocar el cursor de la letra en la mitad superior
    coordenadaX = ancho / 2;
    coordenadaY = 0;
    
    // Configurar la consola para mejor visualizacion
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO infoCursor;
    GetConsoleCursorInfo(hConsole, &infoCursor);
    infoCursor.bVisible = false; // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &infoCursor);
}

void JuegoLetras::generarLetraAleatoria() {
    // Generar una letra aleatoria entre 'a' y 'z'
    letraActual = 'a' + rand() % 26;
}

void JuegoLetras::limpiarConsola() {
    system("cls");
}

void JuegoLetras::irACoordenada(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void JuegoLetras::dibujar() {
    limpiarConsola();
    
    dibujarBorde();
    
    // Dibujar la cuadricula - empezamos con todos los espacios en blanco
    for (int y = 0; y < alto; ++y) {
        irACoordenada(2, y + 2);  // +2 para dejar espacio para el borde
        std::cout << "|";
        
        for (int x = 0; x < ancho; ++x) {
            std::cout << obtenerCelda(x, y);
        }
        
        std::cout << "|";
    }
    
    // Dibujar la letra actual en la posicion del cursor si esta cayendo
    if (letraCayendo) {
        irACoordenada(2 + coordenadaX + 1, coordenadaY + 2);
        std::cout << letraActual;
    } else {
        irACoordenada(2 + coordenadaX + 1, 1);
        std::cout << letraActual;
    }
    
    // Dibujar informacion adicional
    irACoordenada(2, alto + 3);
    std::cout << "Controles: <- -> para mover, abajo para colocar, q para salir";
    
    irACoordenada(2, alto + 4);
    std::cout << "Proxima letra: " << letraActual;
    
    // Actualizar la consola
    irACoordenada(0, alto + 6);
}

void JuegoLetras::dibujarBorde() {
    // Dibujar borde superior
    irACoordenada(2, 0);
    std::cout << "+";
    for (int x = 0; x < ancho; ++x) {
        std::cout << "-";
    }
    std::cout << "+";
    
    // Dibujar bordes laterales
    for (int y = 0; y < alto + 2; ++y) {
        irACoordenada(1, y + 1);
        std::cout << "|";
        irACoordenada(ancho + 2, y + 1);
        std::cout << "|";
    }
    
    // Dibujar borde inferior
    irACoordenada(2, alto + 2);
    std::cout << "+";
    for (int x = 0; x < ancho; ++x) {
        std::cout << "-";
    }
    std::cout << "+";
}

void JuegoLetras::procesarEntrada() {
    if (_kbhit()) {
        int tecla = _getch();
        
        // Comprobar las teclas de flecha (que generan dos codigos)
        if (tecla == 224) {
            tecla = _getch();
            
            switch (tecla) {
                case 75:  // Flecha izquierda
                    if (coordenadaX > 0) {
                        --coordenadaX;
                    }
                    break;
                    
                case 77:  // Flecha derecha
                    if (coordenadaX < ancho - 1) {
                        ++coordenadaX;
                    }
                    break;
                    
                case 80:  // Flecha abajo (acelerar caida de letra)
                    if (!letraCayendo) {
                        letraCayendo = true;
                        coordenadaY = 0;
                    } else {
                        coordenadaY += 1;
                    }
                    break;
            }
        }
        else if (tecla == 'q' || tecla == 'Q') {
            juegoTerminado = true;
        }
    }
    
    // Si no esta cayendo ya, iniciar la caida automatica
    if (!letraCayendo) {
        letraCayendo = true;
        coordenadaY = 0;
    }
}

void JuegoLetras::actualizar() {
    // Si la letra esta cayendo, manejar la animacion
    if (letraCayendo) {
        dejarCaerLetra();
        return;
    }
    
    // Verificar coincidencias y eliminarlas
    while (verificarCoincidencias()) {
        eliminarCoincidencias();
        compactarCuadricula();
    }
    
    // Comprobar si el juego ha terminado (si la primera fila tiene alguna letra)
    bool estaLleno = true;
    for (int x = 0; x < ancho; ++x) {
        if (esCeldaVacia(x, 0)) {
            estaLleno = false;
            break;
        }
    }
    
    if (estaLleno) {
        juegoTerminado = true;
    }
}

bool JuegoLetras::verificarCoincidencias() {
    bool encontroCoincidencia = false;
    
    // Crear listas para almacenar coincidencias en cada direccion
    ListaDoblementeEnlazada<Punto> coincidenciasHorizontales;
    ListaDoblementeEnlazada<Punto> coincidenciasVerticales;
    
    // Comprobar coincidencias horizontales
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho - 1; ++x) {
            char caracterActual = obtenerCelda(x, y);
            if (caracterActual != ' ') {
                int contadorCoincidencias = 1;
                int siguienteX = x + 1;
                
                // Contar coincidencias consecutivas en horizontal
                while (siguienteX < ancho && obtenerCelda(siguienteX, y) == caracterActual) {
                    contadorCoincidencias++;
                    siguienteX++;
                }
                
                // Si hay 2 o mas coincidencias, marcarlas
                if (contadorCoincidencias >= 2) {
                    encontroCoincidencia = true;
                    for (int i = x; i < siguienteX; ++i) {
                        coincidenciasHorizontales.agregarAlFinal(Punto(i, y));
                    }
                    x = siguienteX - 1;  // Saltar las coincidencias ya procesadas
                }
            }
        }
    }
    
    // Comprobar coincidencias verticales
    for (int x = 0; x < ancho; ++x) {
        for (int y = 0; y < alto - 1; ++y) {
            char caracterActual = obtenerCelda(x, y);
            if (caracterActual != ' ') {
                int contadorCoincidencias = 1;
                int siguienteY = y + 1;
                
                // Contar coincidencias consecutivas en vertical
                while (siguienteY < alto && obtenerCelda(x, siguienteY) == caracterActual) {
                    contadorCoincidencias++;
                    siguienteY++;
                }
                
                // Si hay 2 o mas coincidencias, marcarlas
                if (contadorCoincidencias >= 2) {
                    encontroCoincidencia = true;
                    for (int i = y; i < siguienteY; ++i) {
                        coincidenciasVerticales.agregarAlFinal(Punto(x, i));
                    }
                    y = siguienteY - 1;  // Saltar las coincidencias ya procesadas
                }
            }
        }
    }
    
    // Combinar y eliminar coincidencias unicas
    ListaDoblementeEnlazada<Punto> celdasUnicasAEliminar;
    
    // Funcion auxiliar para verificar si un punto ya esta en la lista
    auto esPuntoUnico = [&celdasUnicasAEliminar](const Punto& p) {
        for (int i = 0; i < celdasUnicasAEliminar.obtenerTamano(); ++i) {
            if (celdasUnicasAEliminar.obtener(i) == p) {
                return false;
            }
        }
        return true;
    };
    
    // Agregar coincidencias horizontales unicas
    for (int i = 0; i < coincidenciasHorizontales.obtenerTamano(); ++i) {
        Punto p = coincidenciasHorizontales.obtener(i);
        if (esPuntoUnico(p)) {
            celdasUnicasAEliminar.agregarAlFinal(p);
        }
    }
    
    // Agregar coincidencias verticales unicas
    for (int i = 0; i < coincidenciasVerticales.obtenerTamano(); ++i) {
        Punto p = coincidenciasVerticales.obtener(i);
        if (esPuntoUnico(p)) {
            celdasUnicasAEliminar.agregarAlFinal(p);
        }
    }
    
    // Eliminar las celdas marcadas
    for (int i = 0; i < celdasUnicasAEliminar.obtenerTamano(); ++i) {
        Punto p = celdasUnicasAEliminar.obtener(i);
        limpiarCelda(p.obtenerX(), p.obtenerY());
    }
    
    return encontroCoincidencia;
}

void JuegoLetras::eliminarCoincidencias() {
    // Las coincidencias ya se han eliminado en verificarCoincidencias()
}

void JuegoLetras::compactarCuadricula() {
    // Crear estructuras temporales para la compactacion
    ListaDoblementeEnlazada<Celda> cuadriculaCompactada;
    
    // Compactar verticalmente en cada columna
    for (int x = 0; x < ancho; ++x) {
        // Recopilar todas las letras en esta columna, manteniendo su orden original de abajo hacia arriba
        ListaDoblementeEnlazada<char> columna;
        
        for (int y = alto - 1; y >= 0; --y) {
            char c = obtenerCelda(x, y);
            if (c != ' ') {
                columna.agregarAlFinal(c);
            }
        }
        
        // Volver a colocar desde abajo
        int tamanoColumna = columna.obtenerTamano();
        for (int i = 0; i < tamanoColumna; ++i) {
            int y = alto - 1 - i;
            cuadriculaCompactada.agregarAlFinal(Celda(columna.obtener(i), Punto(x, y)));
        }
    }
    
    // Compactar horizontalmente respetando columnas
    ListaDoblementeEnlazada<Celda> cuadriculaCompactadaHorizontal;
    
    // Mapear para mantener posiciones de las columnas con letras
    bool columnaUsada[10] = {false}; // Suponiendo un maximo de 10 columnas
    
    // Primero, marcar que columnas tienen letras
    for (int i = 0; i < cuadriculaCompactada.obtenerTamano(); ++i) {
        Celda& celda = cuadriculaCompactada.obtener(i);
        columnaUsada[celda.obtenerPosicion().obtenerX()] = true;
    }
    
    // Para cada columna que tenga letras, mover letras hacia la izquierda sin romper estructura
    int nuevaColumnaCoordenada = 0;
    for (int x = 0; x < ancho; ++x) {
        if (columnaUsada[x]) {
            // Recopilar letras de esta columna original
            ListaDoblementeEnlazada<Celda> celdasColumna;
            for (int i = 0; i < cuadriculaCompactada.obtenerTamano(); ++i) {
                Celda& celda = cuadriculaCompactada.obtener(i);
                if (celda.obtenerPosicion().obtenerX() == x) {
                    celdasColumna.agregarAlFinal(
                        Celda(celda.obtenerLetra(), 
                              Punto(nuevaColumnaCoordenada, celda.obtenerPosicion().obtenerY()))
                    );
                }
            }
            
            // Añadir estas celdas al nuevo grid
            for (int i = 0; i < celdasColumna.obtenerTamano(); ++i) {
                cuadriculaCompactadaHorizontal.agregarAlFinal(celdasColumna.obtener(i));
            }
            
            nuevaColumnaCoordenada++;
        }
    }
    
    // Reemplazar el grid con la versión totalmente compactada
    cuadricula.limpiar();
    for (int i = 0; i < cuadriculaCompactadaHorizontal.obtenerTamano(); ++i) {
        cuadricula.agregarAlFinal(cuadriculaCompactadaHorizontal.obtener(i));
    }
}


void JuegoLetras::dejarCaerLetra() {
    // Buscar la posicion final donde aterrizara la letra
    int finalY = alto - 1;
    
    // Encontrar la primera posicion ocupada o el fondo
    for (int y = 0; y < alto; ++y) {
        if (!esCeldaVacia(coordenadaX, y)) {
            finalY = y - 1;
            break;
        }
    }
    
    // Si llegamos a la posicion final o superamos el limite
    if (coordenadaY >= finalY || coordenadaY >= alto - 1) {
        // Asegurarnos de que estamos dentro de los limites
        int posicionY = (coordenadaY >= alto) ? alto - 1 : finalY;
        posicionY = (posicionY < 0) ? 0 : posicionY;  // Evitar indices negativos
        
        // Colocar la letra en la posicion
        establecerCelda(coordenadaX, posicionY, letraActual);
        
        // Verificar coincidencias y actualizar
        while (verificarCoincidencias()) {
            eliminarCoincidencias();
            compactarCuadricula();
        }
        
        // Compactar el grid para asegurar que no haya espacios
        compactarCuadricula();
        
        // Generar nueva letra y reiniciar posicion
        generarLetraAleatoria();
        coordenadaX = ancho / 2;
        coordenadaY = 0;
        letraCayendo = false;
    } else {
        // Avanzar la animacion de caida
        coordenadaY++;
    }
}

void JuegoLetras::ejecutar() {
    // Limpiar la consola
    limpiarConsola();
    
    // Mensaje de advertencia
    std::cout << "Ingeniero porfavor tenga en cuenta que los espacios entre columnas son reducidos, " << std::endl;
    std::cout << "por lo que por ejemplo \"a a\" puede parecer que esta junto, pero para la eliminacion " << std::endl;
    std::cout << "debe estar asi \"aa\". El proceso funciona correctamente, recomiendo hacer zoom " << std::endl;
    std::cout << "en la consola para apreciarlo mejor." << std::endl;
    std::cout << std::endl;
    std::cout << "Presione cualquier tecla para jugar..." << std::endl;
    
    // Esperar a que se presione una tecla
    _getch();
    
    // Inicializar el juego
    inicializar();
    
    int contadorFrames = 0;
    const int velocidadCaida = 5;  // Ajusta para cambiar la velocidad de caida
    
    while (!juegoTerminado) {
        dibujar();
        procesarEntrada();
        
        // Manejar la caida automatica con una velocidad controlada
        contadorFrames++;
        if (contadorFrames >= velocidadCaida) {
            actualizar();
            contadorFrames = 0;
        }
        
        Sleep(50);  // Pequena pausa para controlar la velocidad del juego
    }
    
    // Mostrar mensaje de fin de juego
    limpiarConsola();
    std::cout << "Juego terminado!" << std::endl;
    std::cout << "Presiona cualquier tecla para salir..." << std::endl;
    _getch();
}

bool JuegoLetras::esJuegoTerminado() const {
    return juegoTerminado;
}
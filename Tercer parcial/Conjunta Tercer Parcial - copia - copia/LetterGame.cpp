#include "LetterGame.h"

LetterGame::LetterGame(int w, int h) : width(w), height(h), gameOver(false), isLetterFalling(false), currentY(0) {
    // La lista se inicializa automáticamente
}

LetterGame::~LetterGame() {
    // La lista se limpia automáticamente en su destructor
}

char LetterGame::getCell(int x, int y) const {
    // Buscar la celda en la lista
    for (int i = 0; i < grid.getSize(); i++) {
        const Cell& cell = grid.at(i);
        if (cell.getPosition().getX() == x && cell.getPosition().getY() == y) {
            return cell.getLetter();
        }
    }
    
    // Si no se encuentra, devolver espacio en blanco
    return ' ';
}

void LetterGame::setCell(int x, int y, char value) {
    // Primero verificamos si la celda ya existe
    for (int i = 0; i < grid.getSize(); i++) {
        Cell& cell = grid.at(i);
        if (cell.getPosition().getX() == x && cell.getPosition().getY() == y) {
            // Si existe, actualizar su valor
            if (value == ' ') {
                // Si el nuevo valor es espacio, eliminar la celda
                grid.erase(i);
            } else {
                cell.setLetter(value);
            }
            return;
        }
    }
    
    // Si llegamos aquí, la celda no existe
    if (value != ' ') {
        // Solo añadir si no es un espacio en blanco
        grid.pushBack(Cell(value, Point(x, y)));
    }
}

void LetterGame::clearCell(int x, int y) {
    setCell(x, y, ' ');
}

bool LetterGame::isCellEmpty(int x, int y) const {
    return getCell(x, y) == ' ';
}

void LetterGame::initialize() {
    // Establecer la semilla para números aleatorios
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Limpiar el grid (la lista ya estará vacía, pero por si acaso)
    grid.clear();
    
    // Generar la primera letra
    generateRandomLetter();
    
    // Colocar el cursor de la letra en la mitad superior
    currentX = width / 2;
    currentY = 0;
    
    // Configurar la consola para mejor visualización
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void LetterGame::generateRandomLetter() {
    // Generar una letra aleatoria entre 'a' y 'z'
    currentLetter = 'a' + rand() % 26;
}

void LetterGame::clearConsole() {
    system("cls");
}

void LetterGame::gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void LetterGame::draw() {
    clearConsole();
    
    drawBorder();
    
    // Dibujar la cuadrícula - empezamos con todos los espacios en blanco
    for (int y = 0; y < height; ++y) {
        gotoxy(2, y + 2);  // +2 para dejar espacio para el borde
        std::cout << "|";
        
        for (int x = 0; x < width; ++x) {
            std::cout << getCell(x, y);
        }
        
        std::cout << "|";
    }
    
    // Dibujar la letra actual en la posición del cursor si está cayendo
    if (isLetterFalling) {
        gotoxy(2 + currentX + 1, currentY + 2);
        std::cout << currentLetter;
    } else {
        gotoxy(2 + currentX + 1, 1);
        std::cout << currentLetter;
    }
    
    // Dibujar información adicional
    gotoxy(2, height + 3);
    std::cout << "Controles: ← → para mover, ↓ para colocar, q para salir";
    
    gotoxy(2, height + 4);
    std::cout << "Próxima letra: " << currentLetter;
    
    // Actualizar la consola
    gotoxy(0, height + 6);
}

void LetterGame::drawBorder() {
    // Dibujar borde superior
    gotoxy(2, 0);
    std::cout << "+";
    for (int x = 0; x < width; ++x) {
        std::cout << "-";
    }
    std::cout << "+";
    
    // Dibujar bordes laterales
    for (int y = 0; y < height + 2; ++y) {
        gotoxy(1, y + 1);
        std::cout << "|";
        gotoxy(width + 2, y + 1);
        std::cout << "|";
    }
    
    // Dibujar borde inferior
    gotoxy(2, height + 2);
    std::cout << "+";
    for (int x = 0; x < width; ++x) {
        std::cout << "-";
    }
    std::cout << "+";
}

void LetterGame::processInput() {
    if (_kbhit()) {
        int key = _getch();
        
        // Comprobar las teclas de flecha (que generan dos códigos)
        if (key == 224) {
            key = _getch();
            
            switch (key) {
                case 75:  // Flecha izquierda
                    if (currentX > 0) {
                        --currentX;
                    }
                    break;
                    
                case 77:  // Flecha derecha
                    if (currentX < width - 1) {
                        ++currentX;
                    }
                    break;
                    
                case 80:  // Flecha abajo (acelerar caída de letra)
                    if (!isLetterFalling) {
                        isLetterFalling = true;
                        currentY = 0;
                    } else {
                        currentY += 1;
                    }
                    break;
            }
        }
        else if (key == 'q' || key == 'Q') {
            gameOver = true;
        }
    }
    
    // Si no está cayendo ya, iniciar la caída automática
    if (!isLetterFalling) {
        isLetterFalling = true;
        currentY = 0;
    }
}

void LetterGame::update() {
    // Si la letra está cayendo, manejar la animación
    if (isLetterFalling) {
        dropLetter();
        return;
    }
    
    // Verificar coincidencias y eliminarlas
    while (checkMatches()) {
        removeMatches();
        compactGrid();
    }
    
    // Comprobar si el juego ha terminado (si la primera fila tiene alguna letra)
    bool isFull = true;
    for (int x = 0; x < width; ++x) {
        if (isCellEmpty(x, 0)) {
            isFull = false;
            break;
        }
    }
    
    if (isFull) {
        gameOver = true;
    }
}

bool LetterGame::checkMatches() {
    bool foundMatch = false;
    
    // Crear una lista temporal para almacenar las posiciones a eliminar
    DoublyLinkedList<Point> cellsToRemove;
    
    // Comprobar coincidencias horizontales
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width - 1; ++x) {
            char currentChar = getCell(x, y);
            if (currentChar != ' ' && currentChar == getCell(x + 1, y)) {
                foundMatch = true;
                cellsToRemove.pushBack(Point(x, y));
                cellsToRemove.pushBack(Point(x + 1, y));
            }
        }
    }
    
    // Comprobar coincidencias verticales
    for (int y = 0; y < height - 1; ++y) {
        for (int x = 0; x < width; ++x) {
            char currentChar = getCell(x, y);
            if (currentChar != ' ' && currentChar == getCell(x, y + 1)) {
                foundMatch = true;
                cellsToRemove.pushBack(Point(x, y));
                cellsToRemove.pushBack(Point(x, y + 1));
            }
        }
    }
    
    // Eliminar las celdas marcadas
    for (int i = 0; i < cellsToRemove.getSize(); ++i) {
        Point p = cellsToRemove.at(i);
        clearCell(p.getX(), p.getY());
    }
    
    return foundMatch;
}

void LetterGame::removeMatches() {
    // Las coincidencias ya se han eliminado en checkMatches()
}

void LetterGame::compactGrid() {
    // Crear estructuras temporales para la compactación
    DoublyLinkedList<Cell> compactedGrid;
    
    // Compactar verticalmente - para cada columna
    for (int x = 0; x < width; ++x) {
        // Recopilar todas las letras en esta columna
        DoublyLinkedList<char> column;
        
        for (int y = 0; y < height; ++y) {
            char c = getCell(x, y);
            if (c != ' ') {
                column.pushBack(c);
            }
        }
        
        // Volver a colocar desde abajo
        int columnSize = column.getSize();
        for (int i = 0; i < columnSize; ++i) {
            int y = height - columnSize + i;
            compactedGrid.pushBack(Cell(column.at(i), Point(x, y)));
        }
    }
    
    // Reemplazar el grid con la versión compactada verticalmente
    grid.clear();
    for (int i = 0; i < compactedGrid.getSize(); ++i) {
        grid.pushBack(compactedGrid.at(i));
    }
    
    // Preparar para compactación horizontal
    DoublyLinkedList<Cell> horizontallyCompactedGrid;
    
    // Ahora compactar horizontalmente - para cada fila
    for (int y = 0; y < height; ++y) {
        // Recopilar todas las letras en esta fila
        DoublyLinkedList<char> row;
        
        for (int x = 0; x < width; ++x) {
            char c = getCell(x, y);
            if (c != ' ') {
                row.pushBack(c);
                clearCell(x, y);  // Limpiar la celda original
            }
        }
        
        // Volver a colocar desde la izquierda
        for (int i = 0; i < row.getSize(); ++i) {
            horizontallyCompactedGrid.pushBack(Cell(row.at(i), Point(i, y)));
        }
    }
    
    // Reemplazar el grid con la versión totalmente compactada
    grid.clear();
    for (int i = 0; i < horizontallyCompactedGrid.getSize(); ++i) {
        grid.pushBack(horizontallyCompactedGrid.at(i));
    }
}

void LetterGame::run() {
    initialize();
    
    int frameCount = 0;
    const int dropSpeed = 5;  // Ajusta para cambiar la velocidad de caída
    
    while (!gameOver) {
        draw();
        processInput();
        
        // Manejar la caída automática con una velocidad controlada
        frameCount++;
        if (frameCount >= dropSpeed) {
            update();
            frameCount = 0;
        }
        
        Sleep(50);  // Pequeña pausa para controlar la velocidad del juego
    }
    
    // Mostrar mensaje de fin de juego
    clearConsole();
    std::cout << "¡Juego terminado!" << std::endl;
    std::cout << "Presiona cualquier tecla para salir..." << std::endl;
    _getch();
}

void LetterGame::dropLetter() {
    // Buscar la posición final donde aterrizará la letra
    int finalY = height - 1;
    
    // Encontrar la primera posición ocupada o el fondo
    for (int y = 0; y < height; ++y) {
        if (!isCellEmpty(currentX, y)) {
            finalY = y - 1;
            break;
        }
    }
    
    // Si llegamos a la posición final o superamos el límite
    if (currentY >= finalY || currentY >= height - 1) {
        // Asegurarnos de que estamos dentro de los límites
        int placeY = (currentY >= height) ? height - 1 : finalY;
        placeY = (placeY < 0) ? 0 : placeY;  // Evitar índices negativos
        
        // Colocar la letra en la posición
        setCell(currentX, placeY, currentLetter);
        
        // Verificar coincidencias y actualizar
        while (checkMatches()) {
            removeMatches();
            compactGrid();
        }
        
        // Compactar el grid para asegurar que no haya espacios
        compactGrid();
        
        // Generar nueva letra y reiniciar posición
        generateRandomLetter();
        currentX = width / 2;
        currentY = 0;
    } else {
        // Avanzar la animación de caída
        currentY++;
    }
}

bool LetterGame::isGameOver() const {
    return gameOver;
}
#include "NQueens.h"
#include <iostream>
#include <thread>
#include <chrono>

NQueens::NQueens(int size) : n(size), steps(0), maxSteps(0) {
    board = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    logFile.open("queens_steps.txt");
    
    // Crear ventana con espacio adicional para etiquetas
    int windowSize = (CELL_SIZE * n) + (2 * WINDOW_PADDING) + (2 * LABEL_PADDING);
    window = new sf::RenderWindow(sf::VideoMode(windowSize, windowSize), "N Queens Solver");
    window->setFramerateLimit(60);
    
    // Cargar fuente
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "Error cargando la fuente" << std::endl;
        exit(1);
    }
    
    if (!queenTexture.loadFromFile("queen.png")) {
        std::cout << "Error cargando la imagen de la reina" << std::endl;
        exit(1);
    }
    
    queenSprite.setTexture(queenTexture);
    float scale = static_cast<float>(CELL_SIZE) / queenTexture.getSize().x * 0.8f;
    queenSprite.setScale(scale, scale);
    
    cellShape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    
    clearBoard();
}

NQueens::~NQueens() {
    if (logFile.is_open()) {
        logFile.close();
    }
    delete window;
}

void NQueens::drawBoardLabels() {
    // Dibujar números (filas)
    for (int i = 0; i < n; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(i + 1));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(
            LABEL_PADDING / 2,
            WINDOW_PADDING + LABEL_PADDING + i * CELL_SIZE + CELL_SIZE/3
        );
        window->draw(text);
    }
    
    // Dibujar letras (columnas)
    for (int i = 0; i < n; i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(std::string(1, char('A' + i)));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(
            WINDOW_PADDING + LABEL_PADDING + i * CELL_SIZE + CELL_SIZE/3,
            LABEL_PADDING / 2
        );
        window->draw(text);
    }
}

void NQueens::drawMoveMarkers() {
    sf::CircleShape marker(5);
    marker.setFillColor(sf::Color(255, 0, 0, 180)); // Rojo semitransparente

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 2) {
                marker.setPosition(
                    WINDOW_PADDING + LABEL_PADDING + j * CELL_SIZE + CELL_SIZE/2 - 5,
                    WINDOW_PADDING + LABEL_PADDING + i * CELL_SIZE + CELL_SIZE/2 - 5
                );
                window->draw(marker);
            }
        }
    }
}

sf::Vector2i NQueens::getBoardPosition(sf::Vector2i mousePos) {
    int x = mousePos.x - WINDOW_PADDING - LABEL_PADDING;
    int y = mousePos.y - WINDOW_PADDING - LABEL_PADDING;
    
    if (x >= 0 && y >= 0) {
        int col = x / CELL_SIZE;
        int row = y / CELL_SIZE;
        if (row < n && col < n) {
            return sf::Vector2i(row, col);
        }
    }
    return sf::Vector2i(-1, -1);
}

void NQueens::showQueenMoves(int row, int col) {
    clearBoard();
    board[row][col] = 1;
    
    // Marcar movimientos posibles con 2
    // Horizontal
    for (int j = 0; j < n; j++) {
        if (j != col) board[row][j] = 2;
    }
    
    // Vertical
    for (int i = 0; i < n; i++) {
        if (i != row) board[i][col] = 2;
    }
    
    // Diagonales
    for (int i = 1; i < n; i++) {
        // Superior izquierda
        if (row-i >= 0 && col-i >= 0) board[row-i][col-i] = 2;
        // Superior derecha
        if (row-i >= 0 && col+i < n) board[row-i][col+i] = 2;
        // Inferior izquierda
        if (row+i < n && col-i >= 0) board[row+i][col-i] = 2;
        // Inferior derecha
        if (row+i < n && col+i < n) board[row+i][col+i] = 2;
    }
    
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
                    sf::Vector2i boardPos = getBoardPosition(mousePos);
                    
                    if (boardPos.x != -1 && boardPos.y != -1) {
                        // Actualizar posición de la reina y recalcular movimientos
                        clearBoard();
                        showQueenMoves(boardPos.x, boardPos.y);
                        return;
                    }
                }
            }
        }
        
        window->clear(sf::Color::White);
        
        // Dibujar tablero
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cellShape.setPosition(
                    WINDOW_PADDING + LABEL_PADDING + j * CELL_SIZE,
                    WINDOW_PADDING + LABEL_PADDING + i * CELL_SIZE
                );
                
                if ((i + j) % 2 == 0) {
                    cellShape.setFillColor(sf::Color(240, 217, 181));
                } else {
                    cellShape.setFillColor(sf::Color(181, 136, 99));
                }
                
                window->draw(cellShape);
            }
        }
        
        // Dibujar etiquetas
        drawBoardLabels();
        
        // Dibujar marcadores de movimiento
        drawMoveMarkers();
        
        // Dibujar reina
        if (board[row][col] == 1) {
            queenSprite.setPosition(
                WINDOW_PADDING + LABEL_PADDING + col * CELL_SIZE + (CELL_SIZE - queenSprite.getGlobalBounds().width) / 2,
                WINDOW_PADDING + LABEL_PADDING + row * CELL_SIZE + (CELL_SIZE - queenSprite.getGlobalBounds().height) / 2
            );
            window->draw(queenSprite);
        }
        
        window->display();
    }
}

void NQueens::clearBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = 0;
        }
    }
}

void NQueens::drawBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cellShape.setPosition(WINDOW_PADDING + j * CELL_SIZE, WINDOW_PADDING + i * CELL_SIZE);
            
            if ((i + j) % 2 == 0) {
                cellShape.setFillColor(sf::Color(240, 217, 181)); // Color claro
            } else {
                cellShape.setFillColor(sf::Color(181, 136, 99)); // Color oscuro
            }
            
            window->draw(cellShape);
        }
    }
}

void NQueens::drawQueens() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                queenSprite.setPosition(
                    WINDOW_PADDING + j * CELL_SIZE + (CELL_SIZE - queenSprite.getGlobalBounds().width) / 2,
                    WINDOW_PADDING + i * CELL_SIZE + (CELL_SIZE - queenSprite.getGlobalBounds().height) / 2
                );
                window->draw(queenSprite);
            }
        }
    }
}

void NQueens::handleEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            // Removido el exit(0) para permitir volver al menú
        }
    }
}

bool NQueens::isSafe(int row, int col) {
    for (int i = 0; i < col; i++) {
        if (board[row][i] == 1) return false;
    }
    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }
    
    for (int i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) return false;
    }
    
    return true;
}

void NQueens::printBoardToFile(int row, int col) {
    steps++;
    maxSteps = std::max(maxSteps, steps);
    
    logFile << "Paso " << steps << ":\n";
    logFile << "Colocando reina en posición (" << row + 1 << "," << col + 1 << ")\n";
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            logFile << (board[i][j] ? "Q " : ". ");
        }
        logFile << "\n";
    }
    logFile << "\n";
}

bool NQueens::solveNQueens(int col) {
    if (col >= n) return true;

    for (int i = 0; i < n; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            printBoardToFile(i, col);

            // Actualizar visualización
            window->clear(sf::Color::White);
            drawBoard();
            drawQueens();
            window->display();
            
            handleEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (solveNQueens(col + 1)) return true;

            board[i][col] = 0; // Backtrack
            steps++;
            logFile << "Paso " << steps << ": Retrocediendo - removiendo reina de (" << i + 1 << "," << col + 1 << ")\n\n";
            
            // Actualizar visualización después del backtrack
            window->clear(sf::Color::White);
            drawBoard();
            drawQueens();
            window->display();
            
            handleEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    return false;
}

void NQueens::run() {
    while (window->isOpen()) {
        handleEvents();
        window->clear(sf::Color::White);
        drawBoard();
        drawQueens();
        window->display();
    }
    // No es necesario hacer nada más, simplemente deja que la función termine
}
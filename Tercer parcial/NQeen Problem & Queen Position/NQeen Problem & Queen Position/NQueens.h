#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>

class NQueens {
private:
    int n;
    std::vector<std::vector<int>> board;
    std::ofstream logFile;
    int steps;
    int maxSteps;
    
    // Elementos gráficos
    sf::RenderWindow* window;
    sf::Texture queenTexture;
    sf::Sprite queenSprite;
    sf::RectangleShape cellShape;
    
    // Dimensiones de la ventana y celdas
    const int CELL_SIZE = 80;
    const int WINDOW_PADDING = 50;
    
    bool isSafe(int row, int col);
    void printBoardToFile(int row, int col);
    void clearBoard();
    void drawBoard();
    void drawQueens();
    void handleEvents();
    sf::Font font;
    void drawBoardLabels();
    sf::Vector2i getBoardPosition(sf::Vector2i mousePos);
    void drawMoveMarkers();
    const int LABEL_PADDING = 30;
    
public:
    NQueens(int size);
    ~NQueens();
    bool solveNQueens(int col);
    void run();
    int getSteps() const { return steps; }
    int getMaxSteps() const { return maxSteps; }
    void showQueenMoves(int row, int col);
};

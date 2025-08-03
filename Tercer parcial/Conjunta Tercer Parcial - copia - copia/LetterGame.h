#ifndef LETTER_GAME_H
#define LETTER_GAME_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "DoublyLinkedList.h"
#include "Cell.h"
#include "Point.h"

class LetterGame {
private:
    // Lista de celdas ocupadas en el grid
    DoublyLinkedList<Cell> grid;
    
    int width;
    int height;
    char currentLetter;
    int currentX;
    int currentY;
    bool gameOver;
    bool isLetterFalling;
    
    // Métodos privados
    void generateRandomLetter();
    void clearConsole();
    void gotoxy(int x, int y);
    bool checkMatches();
    void removeMatches();
    void compactGrid();
    void drawBorder();
    
    // Métodos para manipular el grid usando listas
    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);
    void clearCell(int x, int y);
    bool isCellEmpty(int x, int y) const;
    
public:
    LetterGame(int w = 10, int h = 15);
    ~LetterGame();
    
    void initialize();
    void draw();
    void processInput();
    void update();
    void run();
    void dropLetter();
    bool isGameOver() const;
};

#endif // LETTER_GAME_H
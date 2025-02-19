#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Graphics {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* queenTexture;
    int boardSize;
    int squareSize;
    const int WINDOW_SIZE = 800;
    std::vector<SDL_Point> queens;

    // Para el pixelado de imagen
    SDL_Surface* pixelateImage(const char* path, int pixelSize);
    void renderBoard();
    void renderQueens();

public:
    Graphics(int size);
    ~Graphics();
    bool init();
    void loadQueenTexture(const char* path);
    void updateBoard(const std::vector<SDL_Point>& newQueens);
    void render();
    void saveToFile(const char* filename);
    void delay(int ms) { SDL_Delay(ms); }
};

#endif
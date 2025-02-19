#include "graphics.h"
#include <fstream>

Graphics::Graphics(int size) : boardSize(size) {
    window = nullptr;
    renderer = nullptr;
    queenTexture = nullptr;
    squareSize = WINDOW_SIZE / boardSize;
}

Graphics::~Graphics() {
    if(queenTexture) SDL_DestroyTexture(queenTexture);
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
}

bool Graphics::init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    if(IMG_Init(IMG_INIT_PNG) < 0) return false;

    window = SDL_CreateWindow("N-Queens Solver", 
                            SDL_WINDOWPOS_UNDEFINED, 
                            SDL_WINDOWPOS_UNDEFINED,
                            WINDOW_SIZE, 
                            WINDOW_SIZE, 
                            SDL_WINDOW_SHOWN);
    if(!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer) return false;

    return true;
}

SDL_Surface* Graphics::pixelateImage(const char* path, int pixelSize) {
    SDL_Surface* original = IMG_Load(path);
    if(!original) return nullptr;

    SDL_Surface* pixelated = SDL_CreateRGBSurface(0, 
                                                 original->w, 
                                                 original->h,
                                                 32,
                                                 0,0,0,0);

    SDL_LockSurface(original);
    SDL_LockSurface(pixelated);

    Uint32* srcPixels = (Uint32*)original->pixels;
    Uint32* dstPixels = (Uint32*)pixelated->pixels;

    for(int y = 0; y < original->h; y += pixelSize) {
        for(int x = 0; x < original->w; x += pixelSize) {
            Uint32 pixel = srcPixels[y * original->w + x];
            
            for(int py = 0; py < pixelSize && (y + py) < original->h; py++) {
                for(int px = 0; px < pixelSize && (x + px) < original->w; px++) {
                    dstPixels[(y + py) * original->w + (x + px)] = pixel;
                }
            }
        }
    }

    SDL_UnlockSurface(pixelated);
    SDL_UnlockSurface(original);
    SDL_FreeSurface(original);

    return pixelated;
}

void Graphics::loadQueenTexture(const char* path) {
    SDL_Surface* pixelated = pixelateImage(path, 8);
    if(pixelated) {
        queenTexture = SDL_CreateTextureFromSurface(renderer, pixelated);
        SDL_FreeSurface(pixelated);
    }
}

void Graphics::renderBoard() {
    for(int row = 0; row < boardSize; row++) {
        for(int col = 0; col < boardSize; col++) {
            SDL_Rect square = {
                col * squareSize,
                row * squareSize,
                squareSize,
                squareSize
            };

            if((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
            } else {
                SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255); // Dark gray
            }

            SDL_RenderFillRect(renderer, &square);
        }
    }
}

void Graphics::renderQueens() {
    if(!queenTexture) return;

    for(const auto& queen : queens) {
        SDL_Rect destRect = {
            queen.x * squareSize,
            queen.y * squareSize,
            squareSize,
            squareSize
        };
        SDL_RenderCopy(renderer, queenTexture, NULL, &destRect);
    }
}

void Graphics::updateBoard(const std::vector<SDL_Point>& newQueens) {
    queens = newQueens;
    render();
}

void Graphics::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    renderBoard();
    renderQueens();

    SDL_RenderPresent(renderer);
}

void Graphics::saveToFile(const char* filename) {
    SDL_Surface* surface = SDL_CreateRGBSurface(0, WINDOW_SIZE, WINDOW_SIZE, 32, 0, 0, 0, 0);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);
    IMG_SavePNG(surface, filename);
    SDL_FreeSurface(surface);
}
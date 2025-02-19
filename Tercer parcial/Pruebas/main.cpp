#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;

class Laberinto {
private:
    vector<vector<int>> matriz;
    int filas, columnas;
    int numCaminos;
    int caminosEncontrados;
    
    // Direcciones posibles: derecha, abajo, izquierda, arriba
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    
    bool esValido(int x, int y) {
        return x >= 0 && x < filas && y >= 0 && y < columnas && matriz[x][y] == 1;
    }
    
    bool encontrarCamino(int x, int y) {
        if (x == filas-1 && y == columnas-1) {
            caminosEncontrados++;
            return caminosEncontrados == numCaminos;
        }
        
        matriz[x][y] = 2;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (esValido(nx, ny)) {
                if (encontrarCamino(nx, ny)) {
                    return true;
                }
            }
        }
        
        matriz[x][y] = 1;
        return false;
    }

public:
    Laberinto(int n) : filas(10), columnas(10), numCaminos(n), caminosEncontrados(0) {
        matriz = vector<vector<int>>(filas, vector<int>(columnas, 0));
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 1);
        
        matriz[0][0] = 1;
        matriz[filas-1][columnas-1] = 1;
        
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if ((i != 0 || j != 0) && (i != filas-1 || j != columnas-1)) {
                    matriz[i][j] = dis(gen);
                }
            }
        }
    }
    
    void generarLaberinto() {
        encontrarCamino(0, 0);
    }
    
    void guardarEnArchivo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        for (const auto& fila : matriz) {
            for (int valor : fila) {
                archivo << valor << " ";
            }
            archivo << "\n";
        }
        archivo.close();
    }
    
    void dibujarGrafico() {
        sf::RenderWindow window(sf::VideoMode(600, 600), "Laberinto");
        float tamCelda = 50.f;
        
        sf::RectangleShape celda(sf::Vector2f(tamCelda, tamCelda));
        
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            window.clear(sf::Color::White);
            
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    celda.setPosition(j * tamCelda, i * tamCelda);
                    
                    if (matriz[i][j] == 0) {
                        celda.setFillColor(sf::Color::Black);  // Paredes
                    }
                    else if (matriz[i][j] == 2) {
                        celda.setFillColor(sf::Color::Green);  // Camino solución
                    }
                    else {
                        celda.setFillColor(sf::Color::White);  // Espacios libres
                    }
                    
                    celda.setOutlineThickness(1.f);
                    celda.setOutlineColor(sf::Color::Black);
                    window.draw(celda);
                }
            }
            
            window.display();
        }
    }
};

int main() {
    int numCaminos;
    cout << "Ingrese el número de caminos a generar: ";
    cin >> numCaminos;
    
    Laberinto lab(numCaminos);
    lab.generarLaberinto();
    lab.guardarEnArchivo("laberinto.txt");
    lab.dibujarGrafico();
    
    return 0;
}
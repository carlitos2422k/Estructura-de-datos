#pragma once 

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <cmath>
#include <random>
#include <string>

class Grafo {
public:
    Grafo();
    void nuevoGrafo(int numNodos, bool dirigido);
    void representacionLogica();
    void representacionListaAdyacencia();
    void representacionMatrizAdyacencia();
    void busquedaAmplitud(int verticeInicial);
    void mostrarRepresentacionGrafica(const std::string& tipo);

private:
    int numNodos;
    bool dirigido;
    std::vector<std::vector<int>> matrizAdyacencia;
    void generarRelacionesAleatorias();
    
    // SFML specific methods
    void dibujarGrafoLogico(sf::RenderWindow& window);
    void dibujarListaAdyacencia(sf::RenderWindow& window);
    void dibujarMatrizAdyacencia(sf::RenderWindow& window);
    void dibujarFlecha(sf::RenderWindow& window, sf::Vector2f inicio, sf::Vector2f fin);
};

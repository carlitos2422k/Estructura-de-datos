#ifndef JUEGO_LETRAS_H
#define JUEGO_LETRAS_H

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include "ListaDoblementeEnlazada.h"
#include "Celda.h"
#include "Punto.h"

class JuegoLetras {
private:
    // Lista de celdas ocupadas en la cuadricula
    ListaDoblementeEnlazada<Celda> cuadricula;
    
    int ancho;
    int alto;
    char letraActual;
    int coordenadaX;
    int coordenadaY;
    bool juegoTerminado;
    bool letraCayendo;
    
    // Metodos privados
    void generarLetraAleatoria();
    void limpiarConsola();
    void irACoordenada(int x, int y);
    bool verificarCoincidencias();
    void eliminarCoincidencias();
    void compactarCuadricula();
    void dibujarBorde();
    
    // Metodos para manipular la cuadricula usando listas
    char obtenerCelda(int x, int y) const;
    void establecerCelda(int x, int y, char valor);
    void limpiarCelda(int x, int y);
    bool esCeldaVacia(int x, int y) const;
    
public:
    JuegoLetras(int w = 10, int h = 15);
    ~JuegoLetras();
    
    void inicializar();
    void dibujar();
    void procesarEntrada();
    void actualizar();
    void ejecutar();
    void dejarCaerLetra();
    bool esJuegoTerminado() const;
};

#endif // JUEGO_LETRAS_H
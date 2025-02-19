#include <iostream> 
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include "graphics.h"
#include <vector>
#include <fstream> //Libreria para crear, leer y escribir archivos de texto

using namespace std;

class reinas {
private:
    /*Variable del tamano cuadrado del tablero*/
    int tam;
    /*Posicion en el eje x*/
    int x;
    /*Posicion en el eje y*/
    int y;
    /*Matriz de char donde se colocaran las reinas*/
    char **matrizA;
    /*Matriz de booleanos*/
    bool **matrizB;
    fstream enter;
    Graphics* graphics;
    std::vector<SDL_Point> currentQueens;
    int solutionCount;


public:
    /*Constructor de la clase*/
    reinas(int);
    /*Este metodo generara la matriz llena con espacios vacios*/
    void GenerarMatrizA();
    /*Este metodo generara la matriz llena de falsos que se mostraran como 0*/
    void GenerarMatrizB();
    /*Este metodo pondra true horizontal, vertical y en la diagonales cada vez que se ingrese una reina*/
    void Reglas(int, int);
    /*Este metodo quita un reina en el caso que este mal ubicada y restablece la matrizB*/
    void Llenar(int, int);
    /*Este metodo guarda e imprime en consola las matrices si se le envia como parametro true imprimira la matrizA caso contrariola matrizB*/
    void Imprimir(bool);
     /*Este metodo colca una letra R en la matrizA en la posicion pasada como parametro*/
    void PonerReina(int, int);
    /*Este metodo realiza la busqueda por profundidad con recursividad*/
    void Respuesta(int, int, int);
    void inicializarGraficos();
    void actualizarGraficos(int fila, int columna, bool añadir);

};
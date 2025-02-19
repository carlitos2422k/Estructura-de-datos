#include "reinas.h"

/*Constructor de la clase*/
reinas::reinas(int t) {
    tam = t;
    enter.open("ReinasSolucion.txt", fstream::out);
    enter << "Soluciones en tablero de " << t << "*"<< t <<endl<<endl;
    
}
/*Este metodo generara la matriz llena con espacios vacios*/
void reinas::GenerarMatrizA() {
    matrizA = (char**) malloc(tam * sizeof (char*));
    for (int i = 0; i < tam; i++) {
        matrizA[i] = (char *) malloc(tam * sizeof (char));
    }

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matrizA[i][j] = ' ';
        }
    }
}
/*Este metodo generara la matriz llena de falsos que se mostraran como 0*/
void reinas::GenerarMatrizB() {
    matrizB = (bool**) malloc(tam * sizeof (bool*));
    for (int i = 0; i < tam; i++) {
        matrizB[i] = (bool *) malloc(tam * sizeof (bool));
    }

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matrizB[i][j] = false;
        }
    }
}
/*Este metodo pondra true horizontal, vertical y en la diagonales cada vez que se ingrese una reina*/
void reinas::Reglas(int filas, int columnas) {
    x = columnas;
    y = filas;
    /*VERTICAL*/
    int aux1 = x;
    int aux2 = 0;
    while (aux2 < tam) {
        matrizB[aux2][aux1] = true;
        aux2++;
    }
    /*HORIZONTAL*/
    aux1 = 0;
    aux2 = y;
    while (aux1 < tam) {
        matrizB[aux2][aux1] = true;
        aux1++;
    }

    /*DIAGONAL "\" */
    aux1 = x;
    aux2 = y;
    while (aux1 > 0 && aux2 > 0) {
        aux1--;
        aux2--;
    }
    while (aux1 < tam && aux2 < tam) {
        matrizB[aux2][aux1] = true;
        aux1++;
        aux2++;
    }

    /*DIAGONAL "/" */
    aux1 = x;
    aux2 = y;
    if (aux1 == tam - 1 && aux2 == tam - 1) {
    } else {
        while (aux1 < tam && aux2 > 0) {
            aux1++;
            aux2--;
        }
        if (x + y >= tam) {
            aux1--;
            aux2++;
        }
        while (aux1 >= 0 && aux2 < tam) {
            matrizB[aux1][aux2] = true;
            aux1--;
            aux2++;
        }
    }
}
/*Este metodo quita un reina en el caso que este mal ubicada y restablece la matrizB*/
void reinas::Llenar(int filas, int columnas) {
    matrizA[filas][columnas] = ' ';
    actualizarGraficos(filas, columnas, false);
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matrizB[i][j] = false;
        }
    }
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            if (matrizA[i][j] == 'R') {
                Reglas(i, j);
            }
        }
    }
}
/*Este metodo guarda e imprime en consola las matrices si se le envia como parametro true imprimira la matrizA caso contrariola matrizB*/
void reinas::Imprimir(bool opcion) {

    if (opcion) {
        solutionCount++;
        std::string filename = "solution_" + std::to_string(solutionCount) + ".png";
        graphics->saveToFile(filename.c_str());
    }
        for (int i = 0; i < tam; i++) {
            //cout << "|";
            enter << "|";
            for (int j = 0; j < tam; j++) {
                //cout << matrizA[i][j] << "|";
                enter << matrizA[i][j] << "|";
            }
            //cout << endl;
            enter << endl;
        }
    } else {
        for (int i = 0; i < tam; i++) {
            //cout << "|";
            enter << "|";
            for (int j = 0; j < tam; j++) {
                //cout << matrizB[i][j] << "|";
                enter << matrizB[i][j] << "|";
            }
            //cout << endl;
            enter << endl;
        }
    }
    //cout << endl;
    enter << endl;

}

void reinas::PonerReina(int filas, int columnas) {
    matrizA[filas][columnas] = 'R';
    actualizarGraficos(filas, columnas, true);
}

/*Este metodo realiza la busqueda por profundidad con recursividad*/
void reinas::Respuesta(int filas, int columnas, int n) {
    PonerReina(filas, columnas);
    Reglas(filas, columnas);
        
    if (n == tam) {
        Imprimir(true);
    } else {
        for (int i = 0; i < tam; i++) {
            if (matrizB[i][columnas + 1] == false) {
                Respuesta(i, columnas + 1, n + 1);
            }
        }
        Llenar(filas, columnas);
    }
}

void reinas::inicializarGraficos() {
    graphics = new Graphics(tam);
    if(!graphics->init()) {
        std::cerr << "Error initializing graphics!" << std::endl;
        return;
    }
    graphics->loadQueenTexture("queen.png");  // Necesitarás una imagen de reina
    solutionCount = 0;
}

void reinas::actualizarGraficos(int fila, int columna, bool añadir) {
    if(añadir) {
        currentQueens.push_back({columna, fila});
    } else {
        for(auto it = currentQueens.begin(); it != currentQueens.end(); ++it) {
            if(it->x == columna && it->y == fila) {
                currentQueens.erase(it);
                break;
            }
        }
    }
    graphics->updateBoard(currentQueens);
    graphics->delay(100);  // Retraso para ver la animación
}

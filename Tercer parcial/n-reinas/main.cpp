#include "reinas.h"
#include <iostream>

int main() {
    int n = 0;
    while (n < 4) {
        cout << "Ingrese el tamaño de la matriz" << endl;
        cin >> n;
        if (n < 4) {
            cout << "Ingrese un numero mayor a 3" << endl;
        }
    }

    reinas *m = new reinas(n);
    m->GenerarMatrizA();
    m->GenerarMatrizB();
    m->inicializarGraficos();
    
    for(int i = 0; i < n; i++) {
        m->GenerarMatrizA();
        m->GenerarMatrizB();
        m->Respuesta(i, 0, 1);
    }
    
    cout << "Finalizo" << endl;
    cout << "Se han guardado las soluciones como imagenes PNG" << endl;
    cout << "Se ha creado el archivo 'ReinasSolucion'" << endl;

    delete m;
    return 0;
}
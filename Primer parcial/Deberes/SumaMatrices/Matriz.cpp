#include "Matriz.h"
#include <stdlib.h>
#include <time.h>
using namespace std;
Matriz::Matriz(){
    srand(time(NULL) * rand()); 
    for (int i = 0; i<MAX; i++){
        for(int j = 0; j<MAX; j++){
            mat[i][j]=(int)((rand()/32768.1)*4);
        }
    }
}

void Matriz::print()const{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cout << mat[i][j] << "\t"; // Imprime cada elemento seguido de un tabulador
        }
        cout << endl; // Nueva línea al final de cada fila
    }
}

int Matriz::sumaRecursivaMatrices(const Matriz& mat1, const Matriz& mat2, int f, int c){
    if ((f == 0) && (c == 0))
        return mat1.getElement(f, c) + mat2.getElement(f, c);
    else {
        if (f > -1) {
            c--;
            if (c >= -1)
                return mat1.getElement(f, c + 1) + mat2.getElement(f, c + 1) + sumaRecursivaMatrices(mat1, mat2, f, c);
            else
                return sumaRecursivaMatrices(mat1, mat2, f - 1, MAX - 1);
        }
    }
    return 0;
}
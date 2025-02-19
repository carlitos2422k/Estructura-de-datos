#include <iostream>
#include "LatinSquare.h"
using namespace std;

int main (){

    int n;
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> n;

    if(n > 0){
        LatinSquare square(n);
        square.generate();
    }else{
        cout << "El tamaño de la matriz debe ser mayor a 0" << endl;
    }
    
    return 0;
}
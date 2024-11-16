#ifndef MATRIZ_H
#define MATRIZ_H

#include <iostream>

class Matriz{
    private:
    static const int MAX =3;
    int mat[MAX][MAX];

    public:
    Matriz(); //Constructor
    void print() const; //metodo para imprimir
    static int sumaRecursivaMatrices(const Matriz& mat1, const Matriz& mat2, int f , int c);

    int getElement(int row, int col)const{
        return mat[row][col];
    }
    static int getMax(){
        return MAX;
    }
};

#endif // MATRIZ_H
#include "Matriz.h"
using namespace std;
int main(){
	
	Matriz mat1, mat2; //creamos dos matrices uwu
	cout << "Matriz 1: " << endl;
	mat1.print();

	cout << "Matriz 2: " << endl;
	mat2.print();

	cout << "\nSuma de matrices es: " << Matriz::sumaRecursivaMatrices(mat1,mat2,Matriz::getMax()-1,Matriz::getMax()-1) << endl;


	return 0;
}
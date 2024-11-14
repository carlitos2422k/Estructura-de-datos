#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

double ingresar (char *);

double ingresar (char *msj){

	char cad[20];
	char c;
	int i=0,punto=0;

	printf("%s", msj);

	while((c=getch())!=13){

        if ((i==0 && c == '-') ){
            printf("%c", c);
			cad[i++]=c;
        }
		else if((c>='0' && c<='9') || (c == '.' && punto == 0 && i > 0)){
                if(c== '.'){
                    punto =1;
                }
			printf("%c", c);
			cad[i++]=c;
		}

	}
    cad[i]='\0';
    double valor= atof(cad);
    printf("\nNumero ingresado: %.2f\n", valor);
	//cout<<*msj<<endl;
	//valor = atoi(cad);


	return valor;

}


int main(){

    double num= ingresar("Ingrese un entero o decimal: ");


	return 0;
}

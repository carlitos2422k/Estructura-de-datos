/*************************
 * UFA-ESPE
 * ALUMNOS:  Leonardo Obando, William Leon
 * FECHA CREACION: Miercoles, 21 de noviembre de 2022
 * FECHA MODIFICACION: Miercoles, 23 de noviembre de 2022
 * Enunciado del problema: Crear los m�todos Insertar, Buscar
 y Eliminar elementos de una lista Simple, Doble y Circular
 * Nivel: TERCERO     NRC: 7999
 *************************/
#include "ListaDoble.cpp"
#include "Nodo.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
#include <algorithm>
#include <sstream>
#include <list>
#include <cctype>
#include <string>
#include <stdlib.h>
using namespace std;

bool esEntero(string);

int main() {
    ListaDoble<int>* listaEnteros = new ListaDoble<int>();
    ListaDoble<float>* listaFloat = new ListaDoble<float>();
    ListaDoble<double>* listaDouble = new ListaDoble<double>();
    ListaDoble<std::string>* listaString = new ListaDoble<std::string>();
    ListaDoble<char>* listaChar = new ListaDoble<char>();
    int opcion, dato_entero;
    float dato_flotante;
    double dato_doble;
    std::string Nombre1, Nombre2,Apellido,correo,Dato;
    char dato_char;
    Validaciones<int> ingresar_entero;
    Validaciones<float> ingresar_flotante;
    Validaciones<double> ingresar_doble;
    Validaciones<std::string> ingresar_string;
    Validaciones<char> ingresar_letra;
    do {
        system("cls");
        cout << "***********Listas Simples***********" << endl;
        cout << "1. Lista de enteros" << endl;
        cout << "2. lista de flotantes" << endl;
        cout << "3. lista de dobles" << endl;
        cout << "4. lista de strings" << endl;
        cout << "5. lista de letras" << endl;
        cout << "6. salir" << endl;
        opcion = ingresar_entero.ingresar("Opcion: ","entero");
        cout << endl;
        switch (opcion) {
        case 1:
            do {
                system("cls");
                cout << "***********Listas Dobles***********" << endl;
                cout << "1. Insertar por la cola" << endl;
                cout << "2. Insertar por la cabeza" << endl;
                cout << "3. Buscar" << endl;
                cout << "4. Eliminar" << endl;
                cout << "5. Mostrar" << endl;
                cout << "6. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a insertar: ", "entero");
                    cout << endl;
                    listaEnteros->Insertar(dato_entero);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a insertar: ", "entero");
                    cout << endl;
                    listaEnteros->InsertarCabeza(dato_entero);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 3:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a buscar: ", "entero");
                    cout << endl;
                    listaEnteros->Buscar(dato_entero);
                    system("pause");
                    break;
                case 4:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a eliminar: ", "entero");
                    cout << endl;
                    listaEnteros->Eliminar(dato_entero);
                    system("pause");
                    break;
                case 5:
                    listaEnteros->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 6);
            break;
        case 2:
            do {
                system("cls");
                cout << "***********Listas Dobles***********" << endl;
                cout << "1. Insertar por la cola" << endl;
                cout << "2. Insertar por la cabeza" << endl;
                cout << "3. Buscar" << endl;
                cout << "4. Eliminar" << endl;
                cout << "5. Mostrar" << endl;
                cout << "6. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a insertar: ", "flotante");
                    cout << endl;
                    listaFloat->Insertar(dato_flotante);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a insertar: ", "flotante");
                    cout << endl;
                    listaFloat->InsertarCabeza(dato_flotante);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 3:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a buscar: ", "flotante");
                    cout << endl;
                    listaFloat->Buscar(dato_flotante);
                    system("pause");
                    break;
                case 4:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a eliminar: ", "flotante");
                    cout << endl;
                    listaFloat->Eliminar(dato_flotante);
                    system("pause");
                    break;
                case 5:
                    listaFloat->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 6);
            break;
        case 3:
            do {
                system("cls");
                cout << "***********Listas Dobles***********" << endl;
                cout << "1. Insertar por la cola" << endl;
                cout << "2. Insertar por la cabeza" << endl;
                cout << "3. Buscar" << endl;
                cout << "4. Eliminar" << endl;
                cout << "5. Mostrar" << endl;
                cout << "6. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a insertar: ", "double");
                    cout << endl;
                    listaDouble->Insertar(dato_doble);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a insertar: ", "double");
                    cout << endl;
                    listaDouble->InsertarCabeza(dato_doble);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 3:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a buscar: ", "double");
                    cout << endl;
                    listaDouble->Buscar(dato_doble);
                    system("pause");
                    break;
                case 4:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a eliminar: ", "double");
                    cout << endl;
                    listaDouble->Eliminar(dato_doble);
                    system("pause");
                    break;
                case 5:
                    listaDouble->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 6);
            break;
        case 4:
            do {
                system("cls");
                cout << "***********Listas Dobles***********" << endl;
                cout << "1. Insertar por la cola" << endl;
                cout << "2. Insertar por la cabeza" << endl;
                cout << "3. Buscar" << endl;
                cout << "4. Eliminar" << endl;
                cout << "5. Mostrar" << endl;
                cout << "6. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;

                switch (opcion) {
                case 1:
                    /*Nombre1 = ingresar_string.ingresar("ingrese su primer nombre: ", "string");
                    cout << endl;
                    Nombre2 = ingresar_string.ingresar("ingrese su segundo nombre: ", "string");
                    cout << endl;
                    Apellido = ingresar_string.ingresar("ingrese su Apellido: ", "string");
                    correo=generarCorreoUnico(Nombre1,Nombre2,Apellido,*lista_string1);
                    lista_string1->Insertar_cabeza(correo);*/
                    Dato=ingresar_string.ingresar("Ingrese una palabra: ", "string");
                    listaString->Insertar(Dato);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    Dato=ingresar_string.ingresar("Ingrese una palabra: ", "string");
                    listaString->InsertarCabeza(Dato);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 3:
                    Nombre1 = ingresar_string.ingresar("ingrese el dato a buscar: ", "string");
                    cout << endl;
                    listaString->Buscar(Nombre1);
                    system("pause");
                    break;
                case 4:
                    Dato = ingresar_string.ingresar("ingrese el dato a eliminar: ", "string");
                    cout << endl;
                    listaString->Eliminar(Dato);
                    system("pause");
                    break;
                case 5:
                    listaString->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 6);
            break;
        case 5:
            do {
                system("cls");
                cout << "***********Listas Dobles***********" << endl;
                cout << "1. Insertar por la cola" << endl;
                cout << "2. Insertar por la cabeza" << endl;
                cout << "3. Buscar" << endl;
                cout << "4. Eliminar" << endl;
                cout << "5. Mostrar" << endl;
                cout << "6. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a insertar: ", "char");
                    cout << endl;
                    listaChar->Insertar(dato_char);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                    case 2:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a insertar: ", "char");
                    cout << endl;
                    listaChar->InsertarCabeza(dato_char);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 3:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a buscar: ", "char");
                    cout << endl;
                    listaChar->Buscar(dato_char);
                    system("pause");
                    break;
                case 4:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a eliminar: ", "char");
                    cout << endl;
                    listaChar->Eliminar(dato_char);
                    system("pause");
                    break;
                case 5:
                    listaChar->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 6:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 6);
            break;
        case 6:
            cout << "Gracias por visitarnos" << endl;
            system("pause");
            break;
        default:
            cout << "Opcion no valida, intente de nuevo" << endl;
            system("pause");
            break;
        }
    } while (opcion != 6);

    
    return 0;
}



   
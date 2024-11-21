/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include "Lista_Simple.cpp"
#include "Nodo.cpp"
#include <iostream>
#include <stdlib.h>
#include "Validaciones.cpp"
#include <algorithm>
#include <sstream>
#include <list>
#include <cctype>
#include <string>
//#include <windows.h>
using namespace std;
bool esPalabraIrrelevante(const string& palabra) {
    string palabraLower = palabra;
    transform(palabraLower.begin(), palabraLower.end(), palabraLower.begin(), ::tolower);

    // Comprobamos si la palabra es "de", "del", "la", "los", "las", "el", "al"
    return (palabraLower == "de" || palabraLower == "del" || palabraLower == "la" || palabraLower == "los" || palabraLower == "las" || palabraLower == "el" || palabraLower == "al");
}

// Función para obtener la primera palabra relevante
string obtenerPrimeraPalabraRelevante(const string& texto) {
    stringstream ss(texto);
    string palabra;

    while (ss >> palabra) {
        if (!esPalabraIrrelevante(palabra)) {
            return palabra; // Retorna la primera palabra relevante
        }
    }
    return ""; // Si no se encuentra ninguna palabra relevante
}
// Función para generar el correo
string generarCorreoUnico(const string& nombre1, const string& nombre2, const string& apellido, Lista_Simple<string>& correosGenerados) {
    string dominio = "@espe.edu.ec";

    // Obtener la primera letra relevante del primer y segundo nombre
    string primeraLetraNombre1 = obtenerPrimeraPalabraRelevante(nombre1).substr(0, 1);
    string primeraLetraNombre2 = obtenerPrimeraPalabraRelevante(nombre2).substr(0, 1);

    // Obtener el apellido relevante completo
    string apellidoRelevante = obtenerPrimeraPalabraRelevante(apellido);

    // Construir el correo base en minúsculas
    string correoBase = primeraLetraNombre1 + primeraLetraNombre2 + apellidoRelevante;
    for (char& c : correoBase) {
        c = tolower(c);
    }

    // Empezar con el correo base más el dominio
    string correo = correoBase + dominio;

    // Verificar si el correo ya existe
    int contador = 1;
    while (correosGenerados.contains(correo)) {
        // Crear una nueva versión con el número antes del dominio
        correo = correoBase + to_string(contador) + dominio;
        contador++;
    }

    // Agregar el correo generado a la lista
    
    return correo;
}




bool esEntero(string);

int main() {
    Lista_Simple<int>* lista_entero = new Lista_Simple<int>();
    Lista_Simple<float>* lista_flotante = new Lista_Simple<float>();
    Lista_Simple<double>* lista_doble = new Lista_Simple<double>();
    Lista_Simple<std::string>* lista_string1 = new Lista_Simple<std::string>();
    Lista_Simple<char>* lista_letras = new Lista_Simple<char>();

    int opcion, dato_entero;
    float dato_flotante;
    double dato_doble;
    std::string Nombre1, Nombre2,Apellido,correo;

    char dato_char;

    Validaciones<int> ingresar_entero;
    Validaciones<float> ingresar_flotante;
    Validaciones<double> ingresar_doble;
    Validaciones<std::string> ingresar_string;
    Validaciones<char> ingresar_letra;

    /*HINSTANCE hDLL = LoadLibrary("ValidDll.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar la DLL.\n";
        return 1;
    }*/


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
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a insertar: ", "entero");
                    cout << endl;
                    lista_entero->Insertar_cabeza(dato_entero);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a buscar: ", "entero");
                    cout << endl;
                    lista_entero->Buscar(dato_entero);
                    system("pause");
                    break;
                case 3:
                    dato_entero = ingresar_entero.ingresar("ingrese el dato a eliminar: ", "entero");
                    cout << endl;
                    lista_entero->Eliminar(dato_entero);
                    system("pause");
                    break;
                case 4:
                    lista_entero->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 2:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a insertar: ", "flotante");
                    cout << endl;
                    lista_flotante->Insertar_cabeza(dato_flotante);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a buscar: ", "flotante");
                    cout << endl;
                    lista_flotante->Buscar(dato_flotante);
                    system("pause");
                    break;
                case 3:
                    dato_flotante = ingresar_flotante.ingresar("ingrese el dato a eliminar: ", "flotante");
                    cout << endl;
                    lista_flotante->Eliminar(dato_flotante);
                    system("pause");
                    break;
                case 4:
                    lista_flotante->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 3:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a insertar: ", "double");
                    cout << endl;
                    lista_doble->Insertar_cabeza(dato_doble);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a buscar: ", "double");
                    cout << endl;
                    lista_doble->Buscar(dato_doble);
                    system("pause");
                    break;
                case 3:
                    dato_doble = ingresar_doble.ingresar("ingrese el dato a eliminar: ", "double");
                    cout << endl;
                    lista_doble->Eliminar(dato_doble);
                    system("pause");
                    break;
                case 4:
                    lista_doble->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 4:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;

                switch (opcion) {
                case 1:
                    Nombre1 = ingresar_string.ingresar("ingrese su primer nombre: ", "string");
                    cout << endl;
                    Nombre2 = ingresar_string.ingresar("ingrese su segundo nombre: ", "string");
                    cout << endl;
                    Apellido = ingresar_string.ingresar("ingrese su Apellido: ", "string");
                    correo=generarCorreoUnico(Nombre1,Nombre2,Apellido,*lista_string1);
                    lista_string1->Insertar_cabeza(correo);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    Nombre1 = ingresar_string.ingresar("ingrese el dato a buscar: ", "string");
                    cout << endl;
                    lista_string1->Buscar(Nombre1);
                    system("pause");
                    break;
                case 3:
                    Nombre1 = ingresar_string.ingresar("ingrese el dato a eliminar: ", "string");
                    cout << endl;
                    lista_string1->Eliminar(Nombre1);
                    system("pause");
                    break;
                case 4:
                    lista_string1->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
            break;
        case 5:
            do {
                system("cls");
                cout << "***********Listas Simples***********" << endl;
                cout << "1. Insertar" << endl;
                cout << "2. Buscar" << endl;
                cout << "3. Eliminar" << endl;
                cout << "4. Mostrar" << endl;
                cout << "5. Salir" << endl;
                opcion = ingresar_entero.ingresar("Opcion: ","entero");
                cout << endl;
                switch (opcion) {
                case 1:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a insertar: ", "char");
                    cout << endl;
                    lista_letras->Insertar_cabeza(dato_char);
                    cout << endl << "Dato ingresado correctamente" << endl;
                    system("pause");
                    break;
                case 2:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a buscar: ", "char");
                    cout << endl;
                    lista_letras->Buscar(dato_char);
                    system("pause");
                    break;
                case 3:
                    dato_char = ingresar_letra.ingresar("ingrese el dato a eliminar: ", "char");
                    cout << endl;
                    lista_letras->Eliminar(dato_char);
                    system("pause");
                    break;
                case 4:
                    lista_letras->Mostrar();
                    cout << endl;
                    system("pause");
                    break;
                case 5:
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo" << endl;
                    system("pause");
                    break;
                }
            } while (opcion != 5);
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

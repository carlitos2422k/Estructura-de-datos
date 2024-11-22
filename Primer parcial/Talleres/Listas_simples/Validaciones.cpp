/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/

#include "Validaciones.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>

using namespace std;

template <typename T>
Validaciones<T>::Validaciones()
{
}

template <typename T>
T Validaciones<T>::ingresar(char *msj, char *tipo)
{
    char cad[10];
    char c;
    int i = 0;
    T valor;
    printf("%s", msj);
    while ((c = getch()) != 13)
    {
        if (tipo == "entero")
        {
            if (c >= '0' && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8)
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
        }
        else if (tipo == "flotante" || tipo == "double")
        {
            if (c >= '0' && c <= '9')
            {
                printf("%c", c);
                cad[i++] = c;
            }
            else if (c == 8)
            {
                if (i > 0)
                {
                    printf("\b \b");
                    i--;
                }
            }
            else if (c == 46)
            {
                bool aux = false;
                for (int j = 0; cad[j] != '\0'; j++)
                {
                    if (cad[j] == 46)
                    {
                        aux = true;
                        break;
                    }
                }
                if (aux == false)
                {
                    printf("%c", c);
                    cad[i++] = c;
                }
            }
        }
else if (tipo == "string")
{
    bool hasLetter = false; // Indicador para verificar si ya se ingresó una letra.
    while (true)
    {
        c = getch();
        if (c == 13) // Enter presionado, salir del bucle.
        {
            break;
        }
        else if (isalpha(c)) // Si es una letra
        {
            printf("%c", c);
            cad[i++] = c;
            hasLetter = true; // Ahora se permiten los espacios.
        }
        else if (c == 32 && hasLetter) // Permite espacios solo si ya hay una letra.
        {
            printf("%c", c);
            cad[i++] = c;
        }
        else if (c == 8) // Manejo de retroceso.
        {
            if (i > 0)
            {
                if (cad[--i] == ' ') // Si el carácter eliminado es un espacio, no cambia el estado de hasLetter.
                {
                    printf("\b \b");
                }
                else if (isalpha(cad[i])) // Si se elimina una letra, verifica si aún quedan letras.
                {
                    printf("\b \b");
                    hasLetter = false;
                    for (int j = 0; j < i; j++)
                    {
                        if (isalpha(cad[j]))
                        {
                            hasLetter = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    cad[i] = '\0'; // Finaliza la cadena correctamente.
    valor = cad; // Asigna el resultado a 'valor'.
}


        else if (tipo == "char")
        {
            if (isalpha(c))
            {
                printf("%c", c);
                valor = c;
                break;
            }
            else if (c == 8)
            {
                if (c >= 'a' && c <= 'z')
                {
                    printf("\b \b");
                }
            }
        }
    }
    cad[i] = '\0';
    if (tipo == "entero")
    {
        int entero;
        entero = atoi(cad);
        return valor = entero;
    }
    else if (tipo == "flotante")
    {
        float flotante;
        for (int j = 0; cad[j] != '\0'; j++)
        {
            flotante = atof(cad);
        }
        return valor = flotante;
    }
    else if (tipo == "double")
    {
        double doble;
        for (int j = 0; cad[j] != '\0'; j++)
        {
            doble = atof(cad);
        }
        return valor = doble;
    }
    else if (tipo == "char")
    {
        return valor;
    }
    else if (tipo == "string")
    {
        for (int j = 0; cad[j] != '\0'; j++)
        {
            valor = valor + cad[j];
        }
        return valor;
    }
}
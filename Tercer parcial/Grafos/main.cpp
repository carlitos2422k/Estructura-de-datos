// Last update: 2021/10/10 12:00
#include <iostream>
#include <limits>
#include "Grafo.h"

void mostrarMenuPrincipal() 
{
    std::cout << "1. Crear grafo grande" << std::endl;
    std::cout << "2. Crear grafo pequeño" << std::endl;
    std::cout << "3. Salir del programa" << std::endl;
}

void mostrarMenuTipoGrafo()
{
    std::cout << "1. Grafo dirigido" << std::endl;
    std::cout << "2. Grafo no dirigido" << std::endl;
}

void mostrarMenuRepresentacion()
{
    std::cout << "1. Mostrar representación lógica" << std::endl;
    std::cout << "2. Mostrar lista de adyacencia" << std::endl;
    std::cout << "3. Mostrar matriz de adyacencia" << std::endl;
    std::cout << "4. Volver al menú principal" << std::endl;
}

int obtenerOpcion()
{
    int opcion;
    while (true)
    {
        std::cin >> opcion;
        if (std::cin.fail() || opcion < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, ingrese un número entero positivo: ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return opcion;
        }
    }
}

int obtenerVertice(int numNodos)
{
    int vertice;
    while (true)
    {
        std::cin >> vertice;
        if (std::cin.fail() || vertice < 0 || vertice >= numNodos)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada inválida. Por favor, ingrese un número entero positivo entre 0 y " << numNodos - 1 << ": ";
        }
        else
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return vertice;
        }
    }
}

int main()
{
    Grafo grafo;
    int opcionPrincipal, opcionTipoGrafo, opcionRepresentacion, verticeInicial;

    do
    {
        mostrarMenuPrincipal();
        std::cout << "Seleccione una opción: ";
        opcionPrincipal = obtenerOpcion();

        if (opcionPrincipal == 1 || opcionPrincipal == 2)
        {
            int numNodos = (opcionPrincipal == 1) ? 18 : 8;
            mostrarMenuTipoGrafo();
            std::cout << "Seleccione el tipo de grafo: ";
            opcionTipoGrafo = obtenerOpcion();
            bool dirigido = (opcionTipoGrafo == 1);

            grafo.nuevoGrafo(numNodos, dirigido);
            std::cout << "Nuevo grafo generado." << std::endl;

            do
            {
                mostrarMenuRepresentacion();
                std::cout << "Seleccione una opción: ";
                opcionRepresentacion = obtenerOpcion();

                switch (opcionRepresentacion)
                {
                case 1:
                    grafo.representacionLogica();
                    grafo.representacionLogicaGrafica();
                    break;
                case 2:
                    grafo.representacionListaAdyacencia();
                    grafo.representacionListaAdyacenciaGrafica();
                    break;
                case 3:
                    grafo.representacionMatrizAdyacencia();
                    grafo.representacionMatrizAdyacenciaGrafica();
                    break;
                case 4:
                    std::cout << "Volviendo al menú principal..." << std::endl;
                    break;
                default:
                    std::cout << "Opción no válida." << std::endl;
                    break;
                }

                if (opcionRepresentacion >= 1 && opcionRepresentacion <= 3)
                {
                    std::cout << "Ingrese el vértice inicial para la búsqueda por amplitud: ";
                    verticeInicial = obtenerVertice(numNodos);
                    grafo.busquedaAmplitud(verticeInicial);
                }

            } while (opcionRepresentacion != 4);
        }
        else if (opcionPrincipal == 3)
        {
            std::cout << "Saliendo del programa..." << std::endl;
        }
        else
        {
            std::cout << "Opción no válida." << std::endl;
        }
    } while (opcionPrincipal != 3);

    return 0;
}
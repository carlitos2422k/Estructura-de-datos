/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista simple                         *
 * Autor:                          Josue Chango, Adonny Calero, Eduardo altamirano     *
 * Fecha de creacion:              18/11/2024                                          *
 * Fecha de modificacion:          18/11/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include "Lista_Simple.h"
using namespace std;


template <typename T>
Lista_Simple<T>::Lista_Simple()
{
    cabeza = NULL;
}

template <typename T>
void Lista_Simple<T>::Insertar_cabeza(T _dato)
{
    Nodo<T>* nuevo = new Nodo(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

/*template<typename T> 
 void Lista_Simple<T>::Insertar_cola(T _dato) {
    Nodo<T>* nuevo = new Nodo(_dato);
    if (cabeza == NULL) {
        cabeza = nuevo;
    }
    else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != NULL) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}*/

template<typename T> 
 void Lista_Simple<T>::Buscar(T _dato) {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            cout << "El dato " << _dato << " si se encuentra en la lista" << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}

template<typename T> 
 void Lista_Simple<T>::Eliminar(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    while (aux != NULL) {
        if (aux->getDato() == _dato) {
            if (anterior == NULL) {
                cabeza = aux->getSiguiente();
            }
            else {
                anterior->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cout << "El dato " << _dato << " se ha eliminado de la lista" << endl;
            return;
        }
        anterior = aux;
        aux = aux->getSiguiente();
    }
    cout << "El dato " << _dato << " no se encuentra en la lista" << endl;
}
template<typename T>
void Lista_Simple<T>::EliminarDato(T _dato) {
    Nodo<T>* aux = cabeza;
    Nodo<T>* anterior = NULL;
    bool eliminado = false;

    while (aux != NULL) {
        if (aux->getDato() == _dato) { // Si el dato coincide
            if (anterior == NULL) {
                // Caso: Nodo a eliminar es la cabeza
                cabeza = aux->getSiguiente();
                delete aux;
                aux = cabeza; // Actualiza la cabeza
            } else {
                // Caso: Nodo a eliminar no es la cabeza
                anterior->setSiguiente(aux->getSiguiente());
                delete aux;
                aux = anterior->getSiguiente(); // Avanza al siguiente nodo
            }
            eliminado = true; // Marcamos que al menos un nodo fue eliminado
        } else {
            anterior = aux;
            aux = aux->getSiguiente(); // Avanza al siguiente nodo
        }
    }

    // Mensaje de confirmación
    if (eliminado) {
        cout << "Todas las ocurrencias del dato '" << _dato << "' fueron eliminadas." << endl;
    } else {
        cout << "El dato '" << _dato << "' no se encontró en la lista." << endl;
    }
}



template<typename T> 
 void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != NULL) {
        cout << aux->getDato() << " -> ";
        aux = aux->getSiguiente();
    }
    cout << "NULL" << endl;
}
template<typename T>
bool Lista_Simple<T>::contains(T _dato) {
    Nodo<T>* aux = cabeza; // Comienza desde el nodo cabeza
    while (aux != NULL) {
        if (aux->getDato() == _dato) { // Si el dato coincide
            return true;
        }
        aux = aux->getSiguiente(); // Avanza al siguiente nodo
    }
    return false; // Si no lo encuentra
}
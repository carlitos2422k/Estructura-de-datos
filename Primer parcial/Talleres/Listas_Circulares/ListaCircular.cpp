#include "ListaCircular.h"
using namespace std;

template<typename T>
ListaCircular<T>::ListaCircular() {
    primero = NULL;
    ultimo = NULL;
}

template<typename T>
void ListaCircular<T>::Insertar(T _dato) {
    Nodo<T>* nuevo = new Nodo<T>(_dato);
    if (primero == NULL) {
        primero = nuevo;
        ultimo = nuevo;
        ultimo->setSiguiente(primero); // Conexión circular
    } else {
        ultimo->setSiguiente(nuevo);
        ultimo = nuevo;
        ultimo->setSiguiente(primero); // Mantener la circularidad
    }
}

template<typename T>
void ListaCircular<T>::Buscar(T _dato) {
    if (primero == NULL) {
        std::cout << "La lista está vacía.\n";
        return;
    }
    Nodo<T>* actual = primero;
    do {
        if (actual->getDato() == _dato) {
            std::cout << "El dato " << _dato << " se encuentra en la lista.\n";
            return;
        }
        actual = actual->getSiguiente();
    } while (actual != primero);
    std::cout << "El dato " << _dato << " no está en la lista.\n";
}

template<typename T>
void ListaCircular<T>::Eliminar(T _dato) {
    if (primero == NULL) {
        std::cout << "La lista está vacía.\n";
        return;
    }
    Nodo<T>* actual = primero;
    Nodo<T>* anterior = NULL;

    do {
        if (actual->getDato() == _dato) {
            if (anterior == NULL) { // Caso: Nodo es el primero
                if (actual == ultimo) {
                    primero = NULL;
                    ultimo = NULL;
                } else {
                    primero = primero->getSiguiente();
                    ultimo->setSiguiente(primero);
                }
            } else {
                anterior->setSiguiente(actual->getSiguiente());
                if (actual == ultimo) {
                    ultimo = anterior;
                }
            }
            delete actual;
            std::cout << "El dato " << _dato << " fue eliminado.\n";
            return;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    } while (actual != primero);

    std::cout << "El dato " << _dato << " no está en la lista.\n";
}

template<typename T>
void ListaCircular<T>::Mostrar() {
    if (primero == NULL) {
        std::cout << "La lista está vacía.\n";
        return;
    }
    Nodo<T>* actual = primero;
    do {
        std::cout << actual->getDato() << " -> ";
        actual = actual->getSiguiente();
    } while (actual != primero);
    std::cout << "(retorno al inicio)\n";
}
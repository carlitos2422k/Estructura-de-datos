#include "ListaDoble.h"

template<typename T>
ListaDoble<T>::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
}

template<typename T>
void ListaDoble<T>::InsertarPorCabeza(T nombre, T apellido, T cedula, T correo) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        nuevo->setSiguiente(cabeza);
        cabeza->setAnterior(nuevo);
        cabeza = nuevo;
    }
}

template<typename T>
void ListaDoble<T>::InsertarPorCola(T nombre, T apellido, T cedula, T correo) {
    NodoDoble<T>* nuevo = new NodoDoble<T>(nombre, apellido, cedula, correo);
    if (cola == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        nuevo->setAnterior(cola);
        cola = nuevo;
    }
}

template<typename T>
void ListaDoble<T>::Mostrar() {
    NodoDoble<T>* aux = cabeza;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
void ListaDoble<T>::BuscarPorCedula(T cedula) {
    NodoDoble<T>* aux = cabeza;
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            cout << "Registro encontrado: " << endl;
            cout << "Nombre: " << aux->getNombre()
                 << ", Apellido: " << aux->getApellido()
                 << ", Cédula: " << aux->getCedula()
                 << ", Correo: " << aux->getCorreo() << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}

template<typename T>
void ListaDoble<T>::EliminarNodoPorCedula(T cedula) {
    NodoDoble<T>* aux = cabeza;
    
    // Buscar el nodo por cédula
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            if (aux == cabeza) {
                cabeza = aux->getSiguiente();
                if (cabeza != nullptr) {
                    cabeza->setAnterior(nullptr);
                }
            } else if (aux == cola) {
                cola = aux->getAnterior();
                if (cola != nullptr) {
                    cola->setSiguiente(nullptr);
                }
            } else {
                aux->getAnterior()->setSiguiente(aux->getSiguiente());
                if (aux->getSiguiente() != nullptr) {
                    aux->getSiguiente()->setAnterior(aux->getAnterior());
                }
            }
            delete aux;
            cout << "Nodo con cédula " << cedula << " eliminado." << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}

template<typename T>
void ListaDoble<T>::EliminarDatosNodoPorCedula(T cedula) {
    NodoDoble<T>* aux = cabeza;
    
    // Buscar el nodo por cédula
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            aux->setNombre(nullptr);
            aux->setApellido(nullptr);
            aux->setCedula(nullptr);
            aux->setCorreo(nullptr);
            cout << "Datos del nodo con cédula " << cedula << " eliminados." << endl;
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}

/*template<typename T>
void ListaDoble<T>::EliminarCampoPorCedula(T cedula) {
    NodoDoble<T>* aux = cabeza;
    
    // Buscar el nodo por cédula
    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            int opcion;
            cout << "Seleccione el campo a eliminar: " << endl;
            cout << "1. Nombre" << endl;
            cout << "2. Apellido" << endl;
            cout << "3. Cedula" << endl;
            cout << "4. Correo" << endl;
            cout << "Ingrese su opción: ";
            cin >> opcion;
            
            switch (opcion) {
                case 1:
                    aux->setNombre(nullptr);
                    cout << "Nombre eliminado." << endl;
                    break;
                case 2:
                    aux->setApellido(nullptr);
                    cout << "Apellido eliminado." << endl;
                    break;
                case 3:
                    aux->setCedula(nullptr);
                    cout << "Cédula eliminada." << endl;
                    break;
                case 4:
                    aux->setCorreo(nullptr);
                    cout << "Correo eliminado." << endl;
                    break;
                default:
                    cout << "Opción no válida." << endl;
            }
            return;
        }
        aux = aux->getSiguiente();
    }
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
*/
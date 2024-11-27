#include "Lista_Simple.h"

template<typename T>
Lista_Simple<T>::Lista_Simple() {
    cabeza = nullptr;
}

template<typename T>
void Lista_Simple<T>::Insertar(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
}

template<typename T>
void Lista_Simple<T>::Mostrar() {
    Nodo<T>* aux = cabeza;
    while (aux != nullptr) {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    }
}

template<typename T>
void Lista_Simple<T>::BuscarPorCedula(T cedula) {
    Nodo<T>* aux = cabeza;
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

// Función auxiliar para buscar un nodo por cédula
template<typename T>
Nodo<T>* Lista_Simple<T>::BuscarNodoPorCedula(T cedula) {
    Nodo<T>* aux = cabeza;

    while (aux != nullptr) {
        if (aux->getCedula() == cedula) {
            return aux; // Nodo encontrado
        }
        aux = aux->getSiguiente();
    }

    return nullptr; // No encontrado
}


// Función para eliminar un nodo por completo
template<typename T>
void Lista_Simple<T>::EliminarNodoPorCedula(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }

    Nodo<T>* nodoAEliminar = BuscarNodoPorCedula(cedula);

    if (nodoAEliminar == nullptr) {
        cout << "Cédula " << cedula << " no encontrada." << endl;
        return;
    }

    if (nodoAEliminar == cabeza) {
        cabeza = cabeza->getSiguiente();
    } else {
        Nodo<T>* anterior = cabeza;
        while (anterior->getSiguiente() != nodoAEliminar) {
            anterior = anterior->getSiguiente();
        }

        anterior->setSiguiente(nodoAEliminar->getSiguiente());
    }

    delete nodoAEliminar;
    cout << "Nodo con cédula " << cedula << " eliminado." << endl;
}


// Función para limpiar los datos de un nodo
template<typename T>
void Lista_Simple<T>::LimpiarDatosNodo(T cedula) {
    Nodo<T>* nodoALimpiar = BuscarNodoPorCedula(cedula);

    if (nodoALimpiar == nullptr) {
        cout << "Cédula " << cedula << " no encontrada." << endl;
        return;
    }

    nodoALimpiar->setNombre("");
    nodoALimpiar->setApellido("");
    nodoALimpiar->setCedula("");
    nodoALimpiar->setCorreo("");

    cout << "Datos del nodo con cédula " << cedula << " limpiados." << endl;
}

/*template<typename T>
void Lista_Simple<T>::ElegirDatoAEliminar(T cedula) {
    Nodo<T>* nodo = BuscarNodoPorCedula(cedula);
    if (nodo == nullptr) {
        cout << "Cédula " << cedula << " no encontrada." << endl;
        return;
    }

    int opcion = 0;  // Empezamos en la primera opción
    while (true) {
        // Mostrar los datos y el menú
        system("cls");  // Limpiar pantalla (funciona en Windows)
        cout << "Datos actuales del nodo:" << endl;
        cout << "1. Nombre: " << nodo->getNombre() << endl;
        cout << "2. Apellido: " << nodo->getApellido() << endl;
        cout << "3. Cédula: " << nodo->getCedula() << endl;
        cout << "4. Correo: " << nodo->getCorreo() << endl;

        cout << "\nUsa las flechas arriba/abajo para elegir y Enter para confirmar." << endl;

        // Navegar con flechas
        switch (_getch()) {
            case 72:  // Flecha arriba
                if (opcion > 0) opcion--;
                break;
            case 80:  // Flecha abajo
                if (opcion < 3) opcion++;
                break;
            case 13:  // Enter
                switch (opcion) {
                    case 0: nodo->setNombre(""); cout << "Nombre eliminado." << endl; break;
                    case 1: nodo->setApellido(""); cout << "Apellido eliminado." << endl; break;
                    case 2: nodo->setCedula(""); cout << "Cédula eliminada." << endl; break;
                    case 3: nodo->setCorreo(""); cout << "Correo eliminado." << endl; break;
                }
                return;
            default:
                break;
        }
    }
}*/

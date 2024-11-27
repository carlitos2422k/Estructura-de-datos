#include "Lista_Circular.h"

template<typename T>
Lista_Circular<T>::Lista_Circular() {
    cabeza = nullptr;
}

template<typename T>
void Lista_Circular<T>::InsertarPorCabeza(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Apuntamos a sí mismo
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;  // Actualizamos la cabeza
    }
}

template<typename T>
void Lista_Circular<T>::InsertarPorCola(T nombre, T apellido, T cedula, T correo) {
    Nodo<T>* nuevo = new Nodo<T>(nombre, apellido, cedula, correo);
    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->setSiguiente(cabeza);  // Apuntamos a sí mismo
    } else {
        Nodo<T>* aux = cabeza;
        while (aux->getSiguiente() != cabeza) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
        nuevo->setSiguiente(cabeza);
    }
}

template<typename T>
void Lista_Circular<T>::Mostrar() {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        cout << "Nombre: " << aux->getNombre()
             << ", Apellido: " << aux->getApellido()
             << ", Cedula: " << aux->getCedula()
             << ", Correo: " << aux->getCorreo() << endl;
        aux = aux->getSiguiente();
    } while (aux != cabeza);
}

template<typename T>
void Lista_Circular<T>::BuscarPorCedula(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    Nodo<T>* aux = cabeza;
    do {
        if (aux->getCedula() == cedula) {
            cout << "Registro encontrado: " << endl;
            cout << "Nombre: " << aux->getNombre()
                 << ", Apellido: " << aux->getApellido()
                 << ", Cedula: " << aux->getCedula()
                 << ", Correo: " << aux->getCorreo() << endl;
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
 
template<typename T>
void Lista_Circular<T>::EliminarNodo(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    
    Nodo<T>* aux = cabeza;
    Nodo<T>* prev = nullptr;
    
    // Si el nodo a eliminar es la cabeza
    if (aux->getCedula() == cedula) {
        if (aux->getSiguiente() == cabeza) {  // Si solo hay un nodo en la lista
            delete aux;
            cabeza = nullptr;
        } else {
            prev = cabeza;
            // Encontramos el nodo anterior al que queremos eliminar
            while (aux->getSiguiente() != cabeza) {
                prev = aux;
                aux = aux->getSiguiente();
            }
            prev->setSiguiente(cabeza);  // Ajustamos el puntero al nodo siguiente de la cabeza
            delete aux;
        }
        cout << "Nodo con cédula " << cedula << " eliminado correctamente." << endl;
        return;
    }
    
    // Si el nodo a eliminar no es la cabeza
    do {
        prev = aux;
        aux = aux->getSiguiente();
        if (aux->getCedula() == cedula) {
            prev->setSiguiente(aux->getSiguiente());
            delete aux;
            cout << "Nodo con cédula " << cedula << " eliminado correctamente." << endl;
            return;
        }
    } while (aux != cabeza);
    
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}

template<typename T>
void Lista_Circular<T>::EliminarDatosNodo(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    
    Nodo<T>* aux = cabeza;
    do {
        if (aux->getCedula() == cedula) {
            aux->setNombre("");  // Limpiamos el nombre
            aux->setApellido("");  // Limpiamos el apellido
            aux->setCedula("");  // Limpiamos la cédula
            aux->setCorreo("");  // Limpiamos el correo
            cout << "Datos del nodo con cédula " << cedula << " eliminados correctamente." << endl;
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
/*
template<typename T>
void Lista_Circular<T>::EliminarCampoNodo(T cedula) {
    if (cabeza == nullptr) {
        cout << "La lista está vacía." << endl;
        return;
    }
    
    Nodo<T>* aux = cabeza;
    do {
        if (aux->getCedula() == cedula) {
            cout << "Registro encontrado: " << endl;
            cout << "Nombre: " << aux->getNombre() << endl;
            cout << "Apellido: " << aux->getApellido() << endl;
            cout << "Cédula: " << aux->getCedula() << endl;
            cout << "Correo: " << aux->getCorreo() << endl;
            cout << "¿Qué campo deseas eliminar? (1: Nombre, 2: Apellido, 3: Cedula, 4: Correo): ";
            
            int opcion;
            cin >> opcion;
            
            switch (opcion) {
                case 1:
                    aux->setNombre("");
                    cout << "Campo 'Nombre' eliminado." << endl;
                    break;
                case 2:
                    aux->setApellido("");
                    cout << "Campo 'Apellido' eliminado." << endl;
                    break;
                case 3:
                    aux->setCedula("");
                    cout << "Campo 'Cédula' eliminado." << endl;
                    break;
                case 4:
                    aux->setCorreo("");
                    cout << "Campo 'Correo' eliminado." << endl;
                    break;
                default:
                    cout << "Opción no válida." << endl;
                    break;
            }
            return;
        }
        aux = aux->getSiguiente();
    } while (aux != cabeza);
    
    cout << "Cédula " << cedula << " no encontrada en la lista." << endl;
}
*/



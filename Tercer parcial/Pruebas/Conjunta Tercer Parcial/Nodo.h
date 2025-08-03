#ifndef NODO_H
#define NODO_H

template<typename T>
class Nodo {
private:
    T datos;
    Nodo* siguiente;
    Nodo* anterior;
    
public:
    Nodo(const T& valor);
    
    T& obtenerDatos();
    const T& obtenerDatos() const;
    Nodo* obtenerSiguiente() const;
    Nodo* obtenerAnterior() const;
    void establecerDatos(const T& valor);
    void establecerSiguiente(Nodo* nodoSiguiente);
    void establecerAnterior(Nodo* nodoAnterior);
};

// Implementación de la plantilla
template<typename T>
Nodo<T>::Nodo(const T& valor) : datos(valor), siguiente(nullptr), anterior(nullptr) {
}

template<typename T>
T& Nodo<T>::obtenerDatos() {
    return datos;
}

template<typename T>
const T& Nodo<T>::obtenerDatos() const {
    return datos;
}

template<typename T>
Nodo<T>* Nodo<T>::obtenerSiguiente() const {
    return siguiente;
}

template<typename T>
Nodo<T>* Nodo<T>::obtenerAnterior() const {
    return anterior;
}

template<typename T>
void Nodo<T>::establecerDatos(const T& valor) {
    datos = valor;
}

template<typename T>
void Nodo<T>::establecerSiguiente(Nodo* nodoSiguiente) {
    siguiente = nodoSiguiente;
}

template<typename T>
void Nodo<T>::establecerAnterior(Nodo* nodoAnterior) {
    anterior = nodoAnterior;
}

#endif // NODO_H
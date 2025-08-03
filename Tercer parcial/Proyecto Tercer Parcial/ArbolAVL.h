#ifndef ARBOL_AVL_H
#define ARBOL_AVL_H

#include "Libro.h"
#include <vector>

// Definición de NodoAVL directamente en el archivo ArbolAVL.h
class NodoAVL {
private:
    Libro* libro;
    NodoAVL* izquierdo;
    NodoAVL* derecho;
    int altura;

public:
    NodoAVL(Libro* libro);
    ~NodoAVL();
    
    Libro* getLibro() const;
    NodoAVL* getIzquierdo() const;
    NodoAVL* getDerecho() const;
    int getAltura() const;
    
    void setLibro(Libro* libro);
    void setIzquierdo(NodoAVL* izquierdo);
    void setDerecho(NodoAVL* derecho);
    void setAltura(int altura);
};

// Implementación de NodoAVL
inline NodoAVL::NodoAVL(Libro* libro) : libro(libro), izquierdo(nullptr), derecho(nullptr), altura(1) {}

inline NodoAVL::~NodoAVL() {
    // Solo liberamos los nodos hijos
    delete izquierdo;
    delete derecho;
}

inline Libro* NodoAVL::getLibro() const {
    return libro;
}

inline NodoAVL* NodoAVL::getIzquierdo() const {
    return izquierdo;
}

inline NodoAVL* NodoAVL::getDerecho() const {
    return derecho;
}

inline int NodoAVL::getAltura() const {
    return altura;
}

inline void NodoAVL::setLibro(Libro* libro) {
    this->libro = libro;
}

inline void NodoAVL::setIzquierdo(NodoAVL* izquierdo) {
    this->izquierdo = izquierdo;
}

inline void NodoAVL::setDerecho(NodoAVL* derecho) {
    this->derecho = derecho;
}

inline void NodoAVL::setAltura(int altura) {
    this->altura = altura;
}

// Definición de ArbolAVL
class ArbolAVL {
private:
    NodoAVL* raiz;
    
    // Métodos auxiliares privados
    int altura(NodoAVL* nodo);
    int factorBalance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* insertarNodo(NodoAVL* nodo, Libro* libro);
    NodoAVL* eliminarNodo(NodoAVL* nodo, const std::string& codigo);
    NodoAVL* nodoValorMinimo(NodoAVL* nodo);
    void inOrdenRecursivo(NodoAVL* nodo, std::vector<Libro*>& libros);
    NodoAVL* buscarNodo(NodoAVL* nodo, const std::string& codigo);
    void destruirArbol(NodoAVL* nodo);
    
public:
    ArbolAVL();
    ~ArbolAVL();
    
    // Operaciones básicas
    void insertar(Libro* libro);
    void eliminar(const std::string& codigo);
    Libro* buscar(const std::string& codigo);
    std::vector<Libro*> buscarPorGenero(const std::string& genero);
    std::vector<Libro*> inOrden();
    bool estaVacio() const;
    
    // Métodos adicionales que podrían ser útiles
    std::vector<Libro*> buscarPorAutor(const std::string& autor);
    std::vector<Libro*> buscarPorTitulo(const std::string& titulo);
    int contarLibros();
    void liberarLibros();

};

#endif

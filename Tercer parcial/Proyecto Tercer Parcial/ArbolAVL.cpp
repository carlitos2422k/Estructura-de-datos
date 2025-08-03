#include "ArbolAVL.h"
#include <algorithm>

ArbolAVL::ArbolAVL() : raiz(nullptr) {}

void ArbolAVL::liberarLibros() {
    std::vector<Libro*> libros = inOrden();
    for (Libro* libro : libros) {
        delete libro;
    }
}

// Modificar el destructor en ArbolAVL.cpp
ArbolAVL::~ArbolAVL() {
    liberarLibros(); // Liberar primero los libros
    destruirArbol(raiz);
}

void ArbolAVL::destruirArbol(NodoAVL* nodo) {
    if (nodo != nullptr) {
        destruirArbol(nodo->getIzquierdo());
        destruirArbol(nodo->getDerecho());
        delete nodo;
    }
}

int ArbolAVL::altura(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return nodo->getAltura();
}

int ArbolAVL::factorBalance(NodoAVL* nodo) {
    if (nodo == nullptr)
        return 0;
    return altura(nodo->getIzquierdo()) - altura(nodo->getDerecho());
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->getIzquierdo();
    NodoAVL* T2 = x->getDerecho();
    
    // Realizar rotación
    x->setDerecho(y);
    y->setIzquierdo(T2);
    
    // Actualizar alturas
    y->setAltura(std::max(altura(y->getIzquierdo()), altura(y->getDerecho())) + 1);
    x->setAltura(std::max(altura(x->getIzquierdo()), altura(x->getDerecho())) + 1);
    
    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->getDerecho();
    NodoAVL* T2 = y->getIzquierdo();
    
    // Realizar rotación
    y->setIzquierdo(x);
    x->setDerecho(T2);
    
    // Actualizar alturas
    x->setAltura(std::max(altura(x->getIzquierdo()), altura(x->getDerecho())) + 1);
    y->setAltura(std::max(altura(y->getIzquierdo()), altura(y->getDerecho())) + 1);
    
    return y;
}

NodoAVL* ArbolAVL::insertarNodo(NodoAVL* nodo, Libro* libro) {
    // Paso 1: Realizar inserción BST normal
    if (nodo == nullptr)
        return new NodoAVL(libro);
        
    if (libro->getCodigo() < nodo->getLibro()->getCodigo())
        nodo->setIzquierdo(insertarNodo(nodo->getIzquierdo(), libro));
    else if (libro->getCodigo() > nodo->getLibro()->getCodigo())
        nodo->setDerecho(insertarNodo(nodo->getDerecho(), libro));
    else
        return nodo; // No permitimos códigos duplicados
        
    // Paso 2: Actualizar altura del nodo actual
    nodo->setAltura(1 + std::max(altura(nodo->getIzquierdo()), altura(nodo->getDerecho())));
    
    // Paso 3: Obtener el factor de balance 
    int balance = factorBalance(nodo);
    
    // Paso 4: Si el nodo está desbalanceado, hay 4 casos
    
    // Caso Izquierda-Izquierda
    if (balance > 1 && libro->getCodigo() < nodo->getIzquierdo()->getLibro()->getCodigo())
        return rotacionDerecha(nodo);
        
    // Caso Derecha-Derecha
    if (balance < -1 && libro->getCodigo() > nodo->getDerecho()->getLibro()->getCodigo())
        return rotacionIzquierda(nodo);
        
    // Caso Izquierda-Derecha
    if (balance > 1 && libro->getCodigo() > nodo->getIzquierdo()->getLibro()->getCodigo()) {
        nodo->setIzquierdo(rotacionIzquierda(nodo->getIzquierdo()));
        return rotacionDerecha(nodo);
    }
    
    // Caso Derecha-Izquierda
    if (balance < -1 && libro->getCodigo() < nodo->getDerecho()->getLibro()->getCodigo()) {
        nodo->setDerecho(rotacionDerecha(nodo->getDerecho()));
        return rotacionIzquierda(nodo);
    }
    
    // Nodo balanceado, retornar sin cambios
    return nodo;
}

NodoAVL* ArbolAVL::nodoValorMinimo(NodoAVL* nodo) {
    NodoAVL* actual = nodo;
    
    // Encontrar la hoja más a la izquierda
    while (actual->getIzquierdo() != nullptr)
        actual = actual->getIzquierdo();
        
    return actual;
}

NodoAVL* ArbolAVL::eliminarNodo(NodoAVL* nodo, const std::string& codigo) {
    // Paso 1: Realizar eliminación BST normal
    if (nodo == nullptr)
        return nodo;
        
    if (codigo < nodo->getLibro()->getCodigo())
        nodo->setIzquierdo(eliminarNodo(nodo->getIzquierdo(), codigo));
    else if (codigo > nodo->getLibro()->getCodigo())
        nodo->setDerecho(eliminarNodo(nodo->getDerecho(), codigo));
    else {
        // Nodo con un solo hijo o sin hijos
        if ((nodo->getIzquierdo() == nullptr) || (nodo->getDerecho() == nullptr)) {
            NodoAVL* temp = nodo->getIzquierdo() ? nodo->getIzquierdo() : nodo->getDerecho();
            
            // Caso sin hijos
            if (temp == nullptr) {
                temp = nodo;
                nodo = nullptr;
            } else {
                // Caso con un hijo
                // Copiar los contenidos del hijo no vacío
                nodo->setLibro(temp->getLibro());
                nodo->setIzquierdo(temp->getIzquierdo());
                nodo->setDerecho(temp->getDerecho());
                temp->setIzquierdo(nullptr);
                temp->setDerecho(nullptr);
            }
            
            delete temp;
        } else {
            // Nodo con dos hijos: obtener el sucesor in-orden (mínimo en el subárbol derecho)
            NodoAVL* temp = nodoValorMinimo(nodo->getDerecho());
            
            // Copiar la información del sucesor in-orden
            nodo->setLibro(temp->getLibro());
            
            // Eliminar el sucesor in-orden
            nodo->setDerecho(eliminarNodo(nodo->getDerecho(), temp->getLibro()->getCodigo()));
        }
    }
    
    // Si el árbol tenía solo un nodo, retornar
    if (nodo == nullptr)
        return nodo;
        
    // Paso 2: Actualizar altura del nodo actual
    nodo->setAltura(1 + std::max(altura(nodo->getIzquierdo()), altura(nodo->getDerecho())));
    
    // Paso 3: Obtener el factor de balance
    int balance = factorBalance(nodo);
    
    // Paso 4: Si el nodo está desbalanceado, hay 4 casos
    
    // Caso Izquierda-Izquierda
    if (balance > 1 && factorBalance(nodo->getIzquierdo()) >= 0)
        return rotacionDerecha(nodo);
        
    // Caso Izquierda-Derecha
    if (balance > 1 && factorBalance(nodo->getIzquierdo()) < 0) {
        nodo->setIzquierdo(rotacionIzquierda(nodo->getIzquierdo()));
        return rotacionDerecha(nodo);
    }
    
    // Caso Derecha-Derecha
    if (balance < -1 && factorBalance(nodo->getDerecho()) <= 0)
        return rotacionIzquierda(nodo);
        
    // Caso Derecha-Izquierda
    if (balance < -1 && factorBalance(nodo->getDerecho()) > 0) {
        nodo->setDerecho(rotacionDerecha(nodo->getDerecho()));
        return rotacionIzquierda(nodo);
    }
    
    return nodo;
}

NodoAVL* ArbolAVL::buscarNodo(NodoAVL* nodo, const std::string& codigo) {
    if (nodo == nullptr || nodo->getLibro()->getCodigo() == codigo)
        return nodo;
        
    if (codigo < nodo->getLibro()->getCodigo())
        return buscarNodo(nodo->getIzquierdo(), codigo);
        
    return buscarNodo(nodo->getDerecho(), codigo);
}

void ArbolAVL::inOrdenRecursivo(NodoAVL* nodo, std::vector<Libro*>& libros) {
    if (nodo != nullptr) {
        inOrdenRecursivo(nodo->getIzquierdo(), libros);
        libros.push_back(nodo->getLibro());
        inOrdenRecursivo(nodo->getDerecho(), libros);
    }
}

// Métodos públicos

void ArbolAVL::insertar(Libro* libro) {
    raiz = insertarNodo(raiz, libro);
}

void ArbolAVL::eliminar(const std::string& codigo) {
    raiz = eliminarNodo(raiz, codigo);
}

Libro* ArbolAVL::buscar(const std::string& codigo) {
    NodoAVL* nodo = buscarNodo(raiz, codigo);
    
    if (nodo == nullptr)
        return nullptr;
        
    return nodo->getLibro();
}

std::vector<Libro*> ArbolAVL::inOrden() {
    std::vector<Libro*> libros;
    inOrdenRecursivo(raiz, libros);
    return libros;
}

bool ArbolAVL::estaVacio() const {
    return raiz == nullptr;
}

// Métodos adicionales

std::vector<Libro*> ArbolAVL::buscarPorAutor(const std::string& autor) {
    std::vector<Libro*> resultado;
    std::vector<Libro*> todos = inOrden();
    
    for (Libro* libro : todos) {
        if (libro->getAutor() == autor) {
            resultado.push_back(libro);
        }
    }
    
    return resultado;
}

std::vector<Libro*> ArbolAVL::buscarPorTitulo(const std::string& titulo) {
    std::vector<Libro*> resultado;
    std::vector<Libro*> todos = inOrden();
    
    for (Libro* libro : todos) {
        if (libro->getTitulo() == titulo) {
            resultado.push_back(libro);
        }
    }
    
    return resultado;
}

int ArbolAVL::contarLibros() {
    return inOrden().size();
}

std::vector<Libro*> ArbolAVL::buscarPorGenero(const std::string& genero) {
    std::vector<Libro*> resultado;
    std::vector<Libro*> todos = inOrden();
    
    for (Libro* libro : todos) {
        if (libro->getGenero() == genero) {
            resultado.push_back(libro);
        }
    }
    
    return resultado;
}
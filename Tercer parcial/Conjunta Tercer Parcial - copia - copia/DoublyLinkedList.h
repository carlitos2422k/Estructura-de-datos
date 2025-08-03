#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdexcept>
#include "Node.h"

template<typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;
    
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    // No permitir copia para simplificar
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    
    int getSize() const;
    bool isEmpty() const;
    
    void pushBack(const T& value);
    void pushFront(const T& value);
    void popBack();
    void popFront();
    
    T& at(int index);
    const T& at(int index) const;
    
    void clear();
    void insert(int index, const T& value);
    void erase(int index);
    
    template<typename Func>
    void forEach(Func func) const;
};

// Implementación de la plantilla

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
    
    size++;
}

template<typename T>
void DoublyLinkedList<T>::pushFront(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
    
    size++;
}

template<typename T>
void DoublyLinkedList<T>::popBack() {
    if (isEmpty()) {
        return;
    }
    
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* temp = tail;
        tail = tail->getPrev();
        tail->setNext(nullptr);
        delete temp;
    }
    
    size--;
}

template<typename T>
void DoublyLinkedList<T>::popFront() {
    if (isEmpty()) {
        return;
    }
    
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node<T>* temp = head;
        head = head->getNext();
        head->setPrev(nullptr);
        delete temp;
    }
    
    size--;
}

template<typename T>
T& DoublyLinkedList<T>::at(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Índice fuera de rango");
    }
    
    Node<T>* current;
    
    // Optimización: acceder desde el extremo más cercano
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }
    } else {
        current = tail;
        for (int i = size - 1; i > index; i--) {
            current = current->getPrev();
        }
    }
    
    return current->getData();
}

template<typename T>
const T& DoublyLinkedList<T>::at(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Índice fuera de rango");
    }
    
    Node<T>* current;
    
    // Optimización: acceder desde el extremo más cercano
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }
    } else {
        current = tail;
        for (int i = size - 1; i > index; i--) {
            current = current->getPrev();
        }
    }
    
    return current->getData();
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* temp = current;
        current = current->getNext();
        delete temp;
    }
    
    head = tail = nullptr;
    size = 0;
}

template<typename T>
void DoublyLinkedList<T>::insert(int index, const T& value) {
    if (index < 0 || index > size) {
        throw std::out_of_range("Índice fuera de rango para inserción");
    }
    
    if (index == 0) {
        pushFront(value);
        return;
    }
    
    if (index == size) {
        pushBack(value);
        return;
    }
    
    // Encontrar el nodo en la posición index
    Node<T>* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }
    } else {
        current = tail;
        for (int i = size - 1; i > index; i--) {
            current = current->getPrev();
        }
    }
    
    // Insertar antes de current
    Node<T>* newNode = new Node<T>(value);
    newNode->setPrev(current->getPrev());
    newNode->setNext(current);
    current->getPrev()->setNext(newNode);
    current->setPrev(newNode);
    
    size++;
}

template<typename T>
void DoublyLinkedList<T>::erase(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Índice fuera de rango para eliminación");
    }
    
    if (index == 0) {
        popFront();
        return;
    }
    
    if (index == size - 1) {
        popBack();
        return;
    }
    
    // Encontrar el nodo en la posición index
    Node<T>* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; i++) {
            current = current->getNext();
        }
    } else {
        current = tail;
        for (int i = size - 1; i > index; i--) {
            current = current->getPrev();
        }
    }
    
    // Eliminar el nodo
    current->getPrev()->setNext(current->getNext());
    current->getNext()->setPrev(current->getPrev());
    delete current;
    
    size--;
}

template<typename T>
template<typename Func>
void DoublyLinkedList<T>::forEach(Func func) const {
    Node<T>* current = head;
    while (current != nullptr) {
        func(current->getData());
        current = current->getNext();
    }
}

#endif // DOUBLY_LINKED_LIST_H
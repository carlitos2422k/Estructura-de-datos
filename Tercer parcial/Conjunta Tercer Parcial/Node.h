#ifndef NODE_H
#define NODE_H

template<typename T>
class Node {
private:
    T data;
    Node* next;
    Node* prev;
    
public:
    Node(const T& value);
    
    T& getData();
    const T& getData() const;
    Node* getNext() const;
    Node* getPrev() const;
    void setData(const T& value);
    void setNext(Node* nextNode);
    void setPrev(Node* prevNode);
};

// Implementación de la plantilla
template<typename T>
Node<T>::Node(const T& value) : data(value), next(nullptr), prev(nullptr) {
}

template<typename T>
T& Node<T>::getData() {
    return data;
}

template<typename T>
const T& Node<T>::getData() const {
    return data;
}

template<typename T>
Node<T>* Node<T>::getNext() const {
    return next;
}

template<typename T>
Node<T>* Node<T>::getPrev() const {
    return prev;
}

template<typename T>
void Node<T>::setData(const T& value) {
    data = value;
}

template<typename T>
void Node<T>::setNext(Node* nextNode) {
    next = nextNode;
}

template<typename T>
void Node<T>::setPrev(Node* prevNode) {
    prev = prevNode;
}

#endif // NODE_H
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Clase Nodo para el árbol B
class BTreeNode {
public:
    vector<int> keys;            // Las claves almacenadas en el nodo
    vector<BTreeNode*> children; // Los hijos del nodo
    bool leaf;                   // ¿Es un nodo hoja?

    BTreeNode(bool leaf) : leaf(leaf) {}

    // Insertar una clave en el nodo
    void insertKey(int key) {
        keys.push_back(key);
        sort(keys.begin(), keys.end());  // Asegurarse de que las claves estén ordenadas
    }
};

// Clase Árbol B
class BTree {
private:
    BTreeNode* root;  // Raíz del árbol B
    int t;            // Grado mínimo del árbol B (el número de claves antes de la división)

    // Dividir un nodo hijo cuando se llena
    void splitChild(BTreeNode* parent, int index, BTreeNode* fullChild) {
        int midKey = fullChild->keys[t - 1];  // Elemento central

        // Crear un nuevo nodo hijo
        BTreeNode* newChild = new BTreeNode(fullChild->leaf);
        
        // Mover las claves a la nueva hoja
        newChild->keys.assign(fullChild->keys.begin() + t, fullChild->keys.end());
        fullChild->keys.resize(t - 1);  // El nodo original ahora tiene la mitad de las claves

        // Si el nodo no es una hoja, mover los hijos
        if (!fullChild->leaf) {
            newChild->children.assign(fullChild->children.begin() + t, fullChild->children.end());
            fullChild->children.resize(t);
        }

        // Insertar el nuevo hijo en el nodo padre
        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->keys.insert(parent->keys.begin() + index, midKey);  // Subir la clave central
    }

    // Insertar en un nodo no lleno
    void insertNonFull(BTreeNode* node, int key) {
        int i = node->keys.size() - 1;

        if (node->leaf) {
            // Si el nodo es una hoja, insertar la clave en el orden correcto
            node->insertKey(key);
        } else {
            // Si el nodo no es hoja, buscar el hijo adecuado
            while (i >= 0 && node->keys[i] > key) {
                i--;
            }
            i++;

            // Si el hijo está lleno, dividirlo
            if (node->children[i]->keys.size() == 2 * t - 1) {
                splitChild(node, i, node->children[i]);

                // Después de dividir, el nuevo hijo puede tener una clave mayor
                if (node->keys[i] < key) {
                    i++;
                }
            }

            // Llamar recursivamente para insertar en el hijo adecuado
            insertNonFull(node->children[i], key);
        }
    }

public:
    // Constructor
    BTree(int t) : t(t), root(nullptr) {}

    // Insertar una clave en el árbol
    void insert(int key) {
        // Si el árbol está vacío, crear una nueva raíz
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->insertKey(key);
        } else {
            // Si la raíz está llena, dividirla
            if (root->keys.size() == 2 * t - 1) {
                BTreeNode* newRoot = new BTreeNode(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0, root);
                root = newRoot;
            }

            // Insertar la clave en el nodo adecuado
            insertNonFull(root, key);
        }
    }

    // Función para imprimir el árbol (en orden)
    void printTree(BTreeNode* node, int level = 0) {
        if (node != nullptr) {
            for (int i = 0; i < node->keys.size(); ++i) {
                if (!node->leaf) {
                    printTree(node->children[i], level + 1);
                }
                cout << string(level * 2, ' ') << node->keys[i] << endl;
            }
            if (!node->leaf) {
                printTree(node->children[node->keys.size()], level + 1);
            }
        }
    }

    // Método público para imprimir el árbol
    void print() {
        printTree(root);
    }
};

int main() {
    // Crear un árbol B con grado mínimo 3
    BTree tree(3);

    // Insertar claves en el árbol
    tree.insert(4);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    tree.insert(15);
    tree.insert(9);
    tree.insert(4);
    tree.insert(4);

    // Imprimir el árbol B
    cout << "Arbol B:" << endl;
    tree.print();

    return 0;
}
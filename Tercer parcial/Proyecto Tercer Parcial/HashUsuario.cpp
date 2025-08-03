#include "HashUsuario.h"
#include <iostream>
#include <bitset>


HashUsuario::HashUsuario() : table(TABLE_SIZE, nullptr), useQuadraticProbing(false), doubleHashing(false) {}

HashUsuario::~HashUsuario() {
    // Limpiar la memoria
    for (auto usuario : table) {
        delete usuario;
    }
}

void HashUsuario::setProbingMethod(bool useQuadratic) {
    useQuadraticProbing = useQuadratic;
}

void HashUsuario::setDoubleHashing(bool useDoubleHashing) {
    doubleHashing = useDoubleHashing;
}

int HashUsuario::hashString(const std::string& str) {
    unsigned long hash = 0;

    // Recorrer la cadena de derecha a izquierda
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        char c = *it;

        // 1. Sumar el valor del carácter al hash
        hash += static_cast<unsigned long>(c);

        // 2. Aplicar XOR y desplazamientos solo si no es el último carácter
        if (it + 1 != str.rend()) {
            unsigned long xorPart = (hash >> 28) & 0xF; // 4 bits más significativos

            hash = (hash << 4) | xorPart;  // Agregar XOR al final del hash
            hash += xorPart << 10;         // Sumar el XOR desplazado 10 posiciones
        }
    }

    // 3. Aplicar módulo para obtener la posición en la tabla
    return hash % TABLE_SIZE;
}

int HashUsuario::doubleHashString(const std::string& str) {
    unsigned long hash = 0;

    // Recorrer la cadena de derecha a izquierda
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        char c = *it;

        // 1. Sumar el valor del carácter al hash
        hash += static_cast<unsigned long>(c);

        // 2. Aplicar XOR y desplazamientos solo si no es el último carácter
        if (it + 1 != str.rend()) {
            unsigned long xorPart = (hash >> 28) & 0xF; // 4 bits más significativos

            hash = (hash << 4) | xorPart;  // Agregar XOR al final del hash
            hash += xorPart << 10;         // Sumar el XOR desplazado 10 posiciones
        }
    }

    return hash;
}

int HashUsuario::hash2(const std::string& str) {
    unsigned long hash = 0;
    for (char c : str) {
        hash = hash * 31 + c;
    }
    return 7 - (hash % 7); // Hash secundario
}

int HashUsuario::probe(int index, int attempt, int hash1) {
    if (useQuadraticProbing) {
        return (index + attempt * attempt) % TABLE_SIZE;
    }

    if (doubleHashing) {
        return (index + attempt * (hash2(std::to_string(hash1)) % 7)) % TABLE_SIZE;
    }

    return (index + attempt) % TABLE_SIZE; // Linear Probing por defecto
}

bool HashUsuario::insert(Usuario* usuario) {
    if (!usuario) return false;
    
    std::string id = usuario->getIdUsuario();
    int index = hashString(id);
    int attempt = 0;
    int originalIndex = index;
    int hash1 = 0;
    
    if (doubleHashing) {
        hash1 = doubleHashString(id);
    }

    while (table[index] != nullptr) {
        // Si el usuario ya existe con el mismo ID, lo actualizamos
        if (table[index]->getIdUsuario() == id) {
            delete table[index];
            table[index] = usuario;
            return true;
        }
        
        attempt++;
        index = probe(originalIndex, attempt, hash1);
        
        if (index == originalIndex) {
            std::cout << "Tabla llena\n";
            return false;
        }
    }
    
    table[index] = usuario;
    return true;
}

Usuario* HashUsuario::find(const std::string& id) {
    int index = hashString(id);
    int attempt = 0;
    int originalIndex = index;
    int hash1 = 0;
    
    if (doubleHashing) {
        hash1 = doubleHashString(id);
    }
    
    while (table[index] != nullptr) {
        if (table[index]->getIdUsuario() == id) {
            return table[index];
        }
        
        attempt++;
        index = probe(originalIndex, attempt, hash1);
        
        if (index == originalIndex) {
            break;
        }
    }
    
    return nullptr;
}

bool HashUsuario::remove(const std::string& id) {
    int index = hashString(id);
    int attempt = 0;
    int originalIndex = index;
    int hash1 = 0;
    
    if (doubleHashing) {
        hash1 = doubleHashString(id);
    }
    
    while (table[index] != nullptr) {
        if (table[index]->getIdUsuario() == id) {
            delete table[index];
            table[index] = nullptr;
            return true;
        }
        
        attempt++;
        index = probe(originalIndex, attempt, hash1);
        
        if (index == originalIndex) {
            break;
        }
    }
    
    return false;
}

void HashUsuario::display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        std::cout << i << ": ";
        if (table[i] == nullptr) {
            std::cout << "---\n";
        } else {
            std::cout << "ID: " << table[i]->getIdUsuario() 
                      << ", Nombre: " << table[i]->getNombre()
                      << ", Contacto: " << table[i]->getContacto() << "\n";
        }
    }
}

bool HashUsuario::esAdmin(const std::string& id) {
    Usuario* usuario = find(id);
    if (!usuario) return false;
    
    // Comprobamos si el usuario es un administrador usando dynamic_cast
    return dynamic_cast<Administrador*>(usuario) != nullptr;
}

bool HashUsuario::autenticar(const std::string& id, const std::string& contrasena) {
    // En una implementación real, deberías verificar la contraseña
    // Para este ejemplo, simplemente verificamos si el usuario existe
    return find(id) != nullptr;
}

std::vector<Usuario*> HashUsuario::obtenerTodosUsuarios() const {
    std::vector<Usuario*> todosUsuarios;
    
    for (Usuario* usuario : table) {
        if (usuario != nullptr) {
            todosUsuarios.push_back(usuario);
        }
    }
    
    return todosUsuarios;
}
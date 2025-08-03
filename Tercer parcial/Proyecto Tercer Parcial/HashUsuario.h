#ifndef HASH_USUARIO_H
#define HASH_USUARIO_H
#include <string>
#include <vector>
#include "Usuario.h"


class HashUsuario {
private:
    static const int TABLE_SIZE = 29;
    std::vector<Usuario*> table;
    bool useQuadraticProbing; // true para Quadratic Probing, false para Linear Probing
    bool doubleHashing; // true para Double Hashing

    int hashString(const std::string& str);
    int probe(int index, int attempt, int hash1);
    int hash2(const std::string& str);
    int doubleHashString(const std::string& str);

public:
    HashUsuario();
    ~HashUsuario();
    void setProbingMethod(bool useQuadratic);
    void setDoubleHashing(bool useDoubleHashing);
    bool insert(Usuario* usuario);
    Usuario* find(const std::string& id);
    bool remove(const std::string& id);
    void display();
    bool esAdmin(const std::string& id);
    bool autenticar(const std::string& id, const std::string& contrasena);
    
    // Obtener todos los usuarios para persistencia
    std::vector<Usuario*> obtenerTodosUsuarios() const;
};

#endif
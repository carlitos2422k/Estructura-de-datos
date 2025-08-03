#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>
#include <algorithm>
#include "Libro.h"
#include <iostream>

class Usuario {
protected:
    std::string id_usuario;
    std::string nombre;
    std::string contacto;
    std::string contrasena;
    std::vector<Libro> prestamos_activos;

public:
    Usuario(std::string id, std::string nombre, std::string contacto, std::string contrasena);
    virtual ~Usuario() = default;

    std::string getIdUsuario() const;
    std::string getNombre() const;
    std::string getContacto() const;
    std::string getContrasena() const;
    std::vector<Libro> getPrestamosActivos() const;

    void setNombre(std::string nombre);
    void setContacto(std::string contacto);
    void setContrasena(std::string contrasena);
    bool verificarContrasena(std::string contrasena) const;
    void agregarPrestamo(Libro libro);
    void removerPrestamo(std::string codigo);
};

// Definición de la clase Administrador como derivada de Usuario
class Administrador : public Usuario {
public:
    Administrador(std::string id, std::string nombre, std::string contacto, std::string contrasena);
    void registrarLibro(Libro libro);
    void eliminarLibro(std::string codigo);
};

#endif
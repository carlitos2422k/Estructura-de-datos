#include "Usuario.h"

// Implementación de la clase Usuario
Usuario::Usuario(std::string id, std::string nombre, std::string contacto, std::string contrasena) 
    : id_usuario(id), nombre(nombre), contacto(contacto), contrasena(contrasena) {}

std::string Usuario::getIdUsuario() const { return id_usuario; }
std::string Usuario::getNombre() const { return nombre; }
std::string Usuario::getContacto() const { return contacto; }
std::string Usuario::getContrasena() const { return contrasena; }
std::vector<Libro> Usuario::getPrestamosActivos() const { return prestamos_activos; }

void Usuario::setNombre(std::string nombre) { this->nombre = nombre; }
void Usuario::setContacto(std::string contacto) { this->contacto = contacto; }
void Usuario::setContrasena(std::string contrasena) { this->contrasena = contrasena; }

bool Usuario::verificarContrasena(std::string contrasena) const { 
    return this->contrasena == contrasena; 
}

void Usuario::agregarPrestamo(Libro libro) { prestamos_activos.push_back(libro); }

void Usuario::removerPrestamo(std::string codigo) {
    prestamos_activos.erase(std::remove_if(prestamos_activos.begin(), prestamos_activos.end(),
        [codigo](Libro &libro) { return libro.getCodigo() == codigo; }), prestamos_activos.end());
}

// Implementación de la clase Administrador
Administrador::Administrador(std::string id, std::string nombre, std::string contacto, std::string contrasena)
    : Usuario(id, nombre, contacto, contrasena) {}

void Administrador::registrarLibro(Libro libro) {
    std::cout << "Libro registrado: " << libro.getTitulo() << std::endl;
}

void Administrador::eliminarLibro(std::string codigo) {
    std::cout << "Libro con codigo " << codigo << " eliminado." << std::endl;
}
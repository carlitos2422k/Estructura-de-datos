#include "Libro.h"

Libro::Libro(std::string titulo, std::string autor, std::string codigo, std::string ubicacion, std::string genero, int copias) 
    : titulo(titulo), autor(autor), codigo(codigo), ubicacion(ubicacion), genero(genero), copias_disponibles(copias) {}
std::string Libro::getTitulo() const { return titulo; }
std::string Libro::getAutor() const { return autor; }
std::string Libro::getCodigo() const { return codigo; }
std::string Libro::getUbicacion() const { return ubicacion; }
int Libro::getCopiasDisponibles() const { return copias_disponibles; }

void Libro::setTitulo(std::string titulo) { this->titulo = titulo; }
void Libro::setAutor(std::string autor) { this->autor = autor; }
void Libro::setCodigo(std::string codigo) { this->codigo = codigo; }
void Libro::setUbicacion(std::string ubicacion) { this->ubicacion = ubicacion; }
void Libro::setCopiasDisponibles(int copias) { this->copias_disponibles = copias; }
std::string Libro::getGenero() const { return genero; }
void Libro::setGenero(std::string genero) { this->genero = genero; }
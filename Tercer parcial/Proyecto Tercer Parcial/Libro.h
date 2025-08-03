#ifndef LIBRO_H
#define LIBRO_H

#include <string>

class Libro {
private:
    std::string titulo;
    std::string autor;
    std::string codigo;
    std::string ubicacion;
    std::string genero;
    int copias_disponibles;

public:
    Libro(std::string titulo, std::string autor, std::string codigo, std::string ubicacion, std::string genero, int copias);
    
    std::string getTitulo() const;
    std::string getAutor() const;
    std::string getCodigo() const;
    std::string getUbicacion() const;
    int getCopiasDisponibles() const;

    void setTitulo(std::string titulo);
    void setAutor(std::string autor);
    void setCodigo(std::string codigo);
    void setUbicacion(std::string ubicacion);
    void setCopiasDisponibles(int copias);
    std::string getGenero() const;
    void setGenero(std::string genero);
};

#endif

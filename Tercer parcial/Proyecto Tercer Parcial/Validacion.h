#ifndef VALIDACION_H
#define VALIDACION_H

#include <string>
#include <regex>

class Validacion {
public:
    
// Función para capturar ID con letras y números
static std::string capturarIdAlfanumerico(const std::string& mensaje);
    
    // Valida un correo electrónico
    static bool validarCorreo(const std::string& correo);
    
    // Valida contraseña (puedes agregar reglas específicas si lo deseas)
    static bool validarContrasena(const std::string& contrasena);

    static std::string capturarNombreAutor(const std::string& mensaje);
    static bool validarCodigoLibro(const std::string& codigo);
    static std::string capturarCodigoLibro(const std::string& mensaje);
};

#endif // VALIDACION_H
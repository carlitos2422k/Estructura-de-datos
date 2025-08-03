#include "Validacion.h"
#include <iostream>
#include <conio.h>
#include <iostream>
#include <conio.h>

std::string Validacion::capturarIdAlfanumerico(const std::string& mensaje) {
    std::string entrada;
    std::cout << mensaje;
    
    while (true) {
        char ch = _getch(); // Captura tecla sin mostrar
        
        // Permitir Enter para finalizar
        if (ch == 13) {
            if (!entrada.empty()) break;
            continue;
        }
        
        // Permitir Backspace
        if (ch == 8) {
            if (!entrada.empty()) {
                std::cout << "\b \b";
                entrada.pop_back();
            }
            continue;
        }
        
        // Solo letras, números
        if (std::isalnum(ch)) {
            entrada += ch;
            std::cout << ch;
        }
    }
    
    std::cout << std::endl;
    return entrada;
}

bool Validacion::validarCorreo(const std::string& correo) {
    // Regex para validar correo electrónico con dominios específicos (.com, .org, .net, .edu)
    std::regex patron(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.(com|org|net|edu)$)");
    return std::regex_match(correo, patron);
}

bool Validacion::validarContrasena(const std::string& contrasena) {
    // Validación básica: longitud mínima de 6 caracteres
    return contrasena.length() >= 6;
}

std::string Validacion::capturarNombreAutor(const std::string& mensaje) {
    std::string entrada;
    std::cout << mensaje;
    
    while (true) {
        char ch = _getch(); // Captura tecla sin mostrar
        
        // Permitir Enter para finalizar
        if (ch == 13) {
            if (!entrada.empty()) break;
            continue;
        }
        
        // Permitir Backspace
        if (ch == 8) {
            if (!entrada.empty()) {
                std::cout << "\b \b";
                entrada.pop_back();
            }
            continue;
        }
        
        // Solo letras (mayúsculas y minúsculas), espacio y punto (para iniciales)
        if ((ch >= 'A' && ch <= 'Z') || 
            (ch >= 'a' && ch <= 'z') || 
            ch == ' ' || ch == '.') {
            entrada += ch;
            std::cout << ch;
        }
    }
    
    std::cout << std::endl;
    return entrada;
}
// Agregar esta función en la clase Validacion (Validacion.h)
bool Validacion::validarCodigoLibro(const std::string& codigo) {
    // Verificar que el código tenga el formato correcto (LXXX donde X son números)
    if (codigo.length() != 4) {
        return false;
    }
    
    if (codigo[0] != 'L') {
        return false;
    }
    
    // Verificar que los siguientes 3 caracteres sean dígitos
    for (int i = 1; i < 4; i++) {
        if (!std::isdigit(codigo[i])) {
            return false;
        }
    }
    
    return true;
}

// Agregar esta función en la clase Validacion (Validacion.h)
std::string Validacion::capturarCodigoLibro(const std::string& mensaje) {
    std::string codigo;
    
    while (true) {
        std::cout << mensaje;
        std::cin >> codigo;
        
        if (validarCodigoLibro(codigo)) {
            return codigo;
        }
        
        std::cout << "Error: El código debe tener el formato LXXX donde X son números.\n";
        std::cout << "Por ejemplo: L001, L123, etc.\n";
    }
    
    return codigo;
}
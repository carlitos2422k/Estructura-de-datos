/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista circular cifrado               *
 * Autor:                          Carlos Perez                                        *
 * Fecha de creacion:              04/12/2024                                          *
 * Fecha de modificacion:          04/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#include "utils.h"
#include <vector>
#include <regex>

bool Utils::validateId(const std::string& idInput) {
    if (idInput.length() != 10) {
        return false;
    }

    long id = std::stol(idInput);  // Convierte el string a un número entero largo
    std::vector<long> digits(10);
    long remainder;
    long doubledDigit;
    long evenPositionSum = 0;
    long oddPositionSum = 0;
    long totalSum;
    long checkDigit;

    // Extraer los dígitos individuales del número
    for (int i = 9; i >= 0; --i) {
        digits[i] = id % 10;
        id /= 10;
    }

    // Procesar los dígitos en las posiciones pares
    for (int i = 0; i < 9; i += 2) {
        doubledDigit = digits[i] * 2;
        if (doubledDigit > 9) {
            doubledDigit -= 9;
        }
        evenPositionSum += doubledDigit;
    }

    // Procesar los dígitos en las posiciones impares
    for (int i = 1; i < 9; i += 2) {
        oddPositionSum += digits[i];
    }

    // Calcular la suma total y el dígito verificador
    totalSum = evenPositionSum + oddPositionSum;
    remainder = totalSum % 10;
    checkDigit = 10 - remainder;
    if (checkDigit == 10) {
        checkDigit = 0;
    }

    // Comparar el dígito verificador calculado con el último dígito
    return checkDigit == digits[9];
}

bool Utils::validateEmail(const std::string& emailInput) {
    // Usamos una expresión regular para validar el correo
    const std::regex pattern(
        R"((^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$))"
    );

    return std::regex_match(emailInput, pattern);
}
void Utils::modifyCharInString(std::string& str, char target, int offset) {
    for (char& c : str) {
        if (c == target) {
            c = static_cast<char>(c + offset); // Incrementa el ASCII solo si coincide
        }
    }
}

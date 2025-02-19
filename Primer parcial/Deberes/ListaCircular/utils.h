/***************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                  *
 * Proposito:                      Programa sobre lista circular cifrado               *
 * Autor:                          Carlos Perez                                        *
 * Fecha de creacion:              04/12/2024                                          *
 * Fecha de modificacion:          04/12/2024                                          *
 * Materia:                        Estructura de datos                                 *
 * NRC :                           1978                                                *
 **************************************************************************************/
#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    // Valida una cédula ecuatoriana
    static bool validateId(const std::string& idInput);

    // Valida un correo electrónico
    static bool validateEmail(const std::string& emailInput);
    static void modifyCharInString(std::string& str, char target, int offset);
};

#endif // UTILS_H

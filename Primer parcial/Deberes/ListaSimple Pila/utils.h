#ifndef UTILS_H
#define UTILS_H

#include <string>

class Utils {
public:
    // Valida una cédula ecuatoriana
    static bool validateId(const std::string& idInput);

    // Valida un correo electrónico
    static bool validateEmail(const std::string& emailInput);
};

#endif // UTILS_H

#include <iostream>

int main() {
    std::cout << "\033[31mThis is red text\033[0m" << std::endl;  // Rojo
    std::cout << "\033[32mThis is green text\033[0m" << std::endl;  // Verde
    std::cout << "\033[33mThis is yellow text\033[0m" << std::endl;  // Amarillo
    std::cout << "\033[34mThis is blue text\033[0m" << std::endl;  // Azul
    std::cout << "\033[35mThis is magenta text\033[0m" << std::endl;  // Magenta
    std::cout << "\033[36mThis is cyan text\033[0m" << std::endl;  // Cian

    return 0;
}
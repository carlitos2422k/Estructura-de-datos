#include <iostream>
#include <windows.h>

// Definir el tipo de función para la función 'ingresar'
typedef int (*IngresarFunc)(char*);

int main() {
    // Cargar la DLL
    HMODULE hLib = LoadLibraryW(L"Validation.dll"); 
    if (!hLib) {
        std::cerr << "No se pudo cargar la DLL" << std::endl;
        return 1;
    }

    // Obtener la dirección de la función 'ingresar'
    IngresarFunc ingresar = (IngresarFunc)GetProcAddress(hLib, "ingresar");
    if (!ingresar) {
        std::cerr << "No se pudo encontrar la función 'ingresar'" << std::endl;
        FreeLibrary(hLib);
        return 1;
    }

    // Usar la función
    char mensaje[] = "Ingrese un número entero: ";
    int resultado = ingresar(mensaje);
    std::cout << "\nNúmero ingresado: " << resultado << std::endl;

    // Liberar la DLL
    FreeLibrary(hLib);

    return 0;
}

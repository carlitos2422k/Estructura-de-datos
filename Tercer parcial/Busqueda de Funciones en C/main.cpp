#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "FunctionExtractor.h"
#include <chrono>
#include <sstream>


void printUsage() {
    std::cout << "Analizador de Complejidad de Funciones C++" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Uso: ./analizador_complejidad <archivo>" << std::endl;
    std::cout << "Ejemplo: ./analizador_complejidad ejemplo.cpp" << std::endl;
}

void printFunctionSummary(const std::vector<Function>& functions) {
    std::cout << "\nSe encontraron " << functions.size() << " funciones:\n";
    std::cout << "----------------------------------------------\n";
    std::cout << std::left 
              << std::setw(30) << "NOMBRE" 
              << std::setw(20) << "TIPO RETORNO" 
              << std::setw(15) << "COMPLEJIDAD" 
              << "TEMPLATE" << std::endl;
    std::cout << "----------------------------------------------\n";
    
    for (const Function& func : functions) {
        std::string fullName = func.namespace_.empty() ? 
                             func.name : 
                             func.namespace_ + "::" + func.name;
        
        std::cout << std::left 
                  << std::setw(30) << fullName
                  << std::setw(20) << func.returnType 
                  << std::setw(15) << func.complexity
                  << (func.isTemplate ? "Sí" : "No") << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::string filePath;
    
    if (argc < 2) {
        printUsage();
        std::cout << "\nIntroduce la ruta del archivo a analizar: ";
        std::getline(std::cin, filePath);
        if (filePath.empty()) {
            std::cerr << "No se especificó ningún archivo. Saliendo..." << std::endl;
            return 1;
        }
    } else {
        // Reconstruir la ruta completa en caso de espacios
        std::stringstream ss;
        for (int i = 1; i < argc; i++) {
            if (i > 1) ss << " ";
            ss << argv[i];
        }
        filePath = ss.str();
        
        // Remover comillas si existen
        if (filePath.front() == '"' && filePath.back() == '"') {
            filePath = filePath.substr(1, filePath.length() - 2);
        }
    }
    
    std::cout << "Ruta completa del archivo: " << filePath << std::endl;
    
    // Verificar que el archivo existe
    std::ifstream fileCheck(filePath);
    if (!fileCheck) {
        std::cerr << "Error: No se puede acceder al archivo en la ruta especificada." << std::endl;
        return 1;
    }
    fileCheck.close();
    
    std::string csvPath = "funciones_extraidas.csv";
    
    try {
        std::cout << "=== Iniciando análisis ===" << std::endl;
        auto startTime = std::chrono::high_resolution_clock::now();
        
        FunctionExtractor extractor;
        std::cout << "Analizando archivo: " << filePath << std::endl;
        std::cout << "Este proceso puede tomar unos segundos..." << std::endl;
        
        std::vector<Function> functions = extractor.extractFromFile(filePath);
        
        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        
        if (functions.empty()) {
            std::cout << "No se encontraron funciones en el archivo." << std::endl;
            return 1;
        }
        
        std::cout << "\nAnálisis completado!" << std::endl;
        std::cout << "Tiempo de procesamiento: " << duration << " ms" << std::endl;
        std::cout << "Funciones encontradas: " << functions.size() << std::endl;
        
        printFunctionSummary(functions);
        
        if (extractor.saveToCSV(functions, "funciones_extraidas.csv")) {
            std::cout << "\nResultados guardados en: funciones_extraidas.csv" << std::endl;
        }
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

}
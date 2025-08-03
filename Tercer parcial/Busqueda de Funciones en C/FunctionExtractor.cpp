#include "FunctionExtractor.h"
#include <fstream>
#include <regex>
#include <stdexcept>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <sys/stat.h>

FunctionExtractor::FunctionExtractor() {}

bool FunctionExtractor::isValidSourceFile(const std::string& filePath) {
    size_t pos = filePath.find_last_of(".");
    if (pos == std::string::npos) return false;
    
    std::string extension = filePath.substr(pos);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    std::unordered_set<std::string> validExtensions = {
        ".cpp", ".cc", ".cxx", ".c", ".h", ".hpp", ".txt", ".exe"
    };
    
    return validExtensions.find(extension) != validExtensions.end();
}

bool FunctionExtractor::fileExists(const std::string& filePath) {
    struct stat buffer;
    return (stat(filePath.c_str(), &buffer) == 0);
}

std::streamsize FunctionExtractor::getFileSize(const std::string& filePath) {
    struct stat buffer;
    if (stat(filePath.c_str(), &buffer) == 0) {
        return buffer.st_size;
    }
    return -1;
}

bool FunctionExtractor::isBinaryFile(const std::string& filePath) {
    std::ifstream file(filePath.c_str(), std::ios::binary);
    if (!file.is_open()) {
        if (!fileExists(filePath)) {
            throw std::runtime_error("El archivo no existe: " + filePath);
        }
        throw std::runtime_error("No se puede abrir el archivo: " + filePath);
    }
    
    // Verificar solo los primeros 4KB
    const size_t SAMPLE_SIZE = 4096;
    char buffer[SAMPLE_SIZE];
    file.read(buffer, SAMPLE_SIZE);
    size_t bytesRead = file.gcount();
    
    size_t binaryCount = 0;
    for (size_t i = 0; i < bytesRead; i++) {
        if (buffer[i] == 0 || (unsigned char)buffer[i] > 127) {
            binaryCount++;
            // Si más del 10% son caracteres binarios, considerarlo binario
            if (binaryCount > bytesRead / 10) {
                return true;
            }
        }
    }
    
    return false;
}

std::string FunctionExtractor::readFile(const std::string& filePath) {
    if (!fileExists(filePath)) {
        throw std::runtime_error("El archivo no existe: " + filePath);
    }

    // Verificar si es binario antes de leer completamente
    if (isBinaryFile(filePath)) {
        std::cout << "Archivo binario detectado: " << filePath << std::endl;
        return analyzeBinaryFile(filePath);
    }

    std::ifstream file(filePath.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("No se puede abrir el archivo: " + filePath);
    }
    
    std::cout << "Leyendo contenido del archivo de texto..." << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::string FunctionExtractor::analyzeBinaryFile(const std::string& filePath) {
    std::stringstream result;
    std::streamsize fileSize = getFileSize(filePath);
    
    result << "// Análisis de archivo binario: " << filePath << "\n\n";
    result << "void main() {\n";
    result << "    // Este es un archivo binario/ejecutable\n";
    if (fileSize >= 0) {
        result << "    // Tamaño: " << fileSize << " bytes\n";
    }
    result << "    // No es posible extraer las funciones originales\n";
    result << "    // Se recomienda analizar el código fuente (.cpp, .c)\n";
    result << "}\n";
    
    return result.str();
}

std::vector<Function> FunctionExtractor::extractFromFile(const std::string& filePath) {
    try {
        std::cout << "Procesando archivo: " << filePath << std::endl;
        
        if (!isValidSourceFile(filePath)) {
            throw std::runtime_error("Extensión de archivo no soportada.\n"
                               "Extensiones válidas: .cpp, .cc, .cxx, .c, .h, .hpp, .exe");
        }
        
        std::cout << "Leyendo archivo..." << std::endl;
        std::string sourceCode = readFile(filePath);
        std::cout << "Extrayendo funciones..." << std::endl;
        clearCurrentFunctions(); // Limpiar funciones anteriores
        auto result = extractFunctions(sourceCode);
        currentFunctions = result; // Guardar las funciones extraídas
        std::cout << "Extracción completada. Encontradas " << result.size() << " funciones." << std::endl;
        return result;
    } catch (const std::exception& e) {
        std::cerr << "Error al extraer funciones: " << e.what() << std::endl;
        return std::vector<Function>();
    }
}

std::vector<Function> FunctionExtractor::extractFunctions(const std::string& sourceCode) {
    std::vector<Function> functions;
    
    try {
        // Palabras clave a excluir
        std::string keywords = "if|else|while|for|switch|case|catch|class|struct|enum|return|break|continue|typedef|template|public|private|protected|virtual|static|friend|operator|typename|using|namespace|constexpr|explicit|noexcept";
        
        // Expresión regular mejorada con bandera de optimización
        std::regex functionPattern(
            // Template opcional
            "(template\\s*<[^>]+>\\s*)?"
            // Calificadores opcionales antes del tipo de retorno
            "(constexpr\\s+|explicit\\s+|inline\\s+)?"
            // Tipo de retorno con posible namespace, punteros y referencias
            "((?:[\\w:]+\\s*(?:<[^>]*>)?\\s*[&*]?\\s*)+)"
            // Nombre de la función, evitando palabras clave
            "(?!(?:" + keywords + ")\\b)"
            "([\\w:]+)\\s*"
            // Parámetros entre paréntesis
            "\\(([^)]*?)\\)"
            // Calificadores finales (const, override, noexcept, etc.)
            "((?:\\s+const|\\s+override|\\s+final|\\s+noexcept)*)\\s*"
            // Apertura de llave
            "\\{",
            std::regex::ECMAScript | std::regex::optimize
        );
        
        auto searchStart = sourceCode.cbegin();
        std::smatch functionMatch;
        
        while (std::regex_search(searchStart, sourceCode.cend(), functionMatch, functionPattern)) {
            Function func;
            
            func.isTemplate = functionMatch[1].matched;
            func.templateParams = func.isTemplate ? functionMatch[1].str() : "";
            func.returnType = functionMatch[3].str();
            func.name = functionMatch[4].str();
            func.parameters = functionMatch[5].str();
            func.qualifiers = functionMatch[6].str();
            
            // Función lambda para limpiar espacios
            auto trimSpaces = [](std::string str) {
                str = std::regex_replace(str, std::regex("^\\s+|\\s+$"), "");
                str = std::regex_replace(str, std::regex("\\s+"), " ");
                return str;
            };
            
            func.returnType = trimSpaces(func.returnType);
            func.name = trimSpaces(func.name);
            func.parameters = trimSpaces(func.parameters);
            func.qualifiers = trimSpaces(func.qualifiers);
            
            // Extraer namespace si existe
            size_t lastColonPos = func.name.rfind("::");
            if (lastColonPos != std::string::npos) {
                func.namespace_ = func.name.substr(0, lastColonPos);
                func.name = func.name.substr(lastColonPos + 2);
            }
            
            // Verificar falsos positivos usando palabras clave
            if (std::regex_match(func.name, std::regex("\\b(" + keywords + ")\\b"))) {
                // Avanzar la búsqueda y continuar
                auto newPos = functionMatch.suffix().first;
                if (newPos == searchStart) break; // Evita bucles infinitos
                searchStart = newPos;
                continue;
            }
            
            // Extraer cuerpo de la función
            size_t bodyStart = functionMatch.position() + functionMatch.length() - 1;
            func.body = extractFunctionBody(sourceCode, bodyStart);
            
            // Analizar complejidad
            func.complexity = analyzeComplexity(func.body);
            
            // Agregar solo funciones válidas
            if (!func.name.empty() && func.body.length() > 2) {
                functions.push_back(func);
                std::cout << "Función encontrada: " << func.name 
                          << (func.isTemplate ? " (template)" : "")
                          << " [" << func.returnType << "]" << std::endl;
            }
            
            // Avanzar la búsqueda y verificar que se avance el iterador
            auto newPos = functionMatch.suffix().first;
            if (newPos == searchStart) {
                std::cerr << "No se avanza la búsqueda. Posible coincidencia nula." << std::endl;
                break;
            }
            searchStart = newPos;
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Error en extractFunctions: " << e.what() << std::endl;
    }
    
    return functions;
}



std::string FunctionExtractor::extractFunctionBody(const std::string& sourceCode, size_t startPos) {
    if (startPos >= sourceCode.length()) return "{}";
    
    std::string body;
    int braceCount = 1;
    size_t pos = startPos;
    bool inString = false;
    bool inChar = false;
    bool inLineComment = false;
    bool inBlockComment = false;
    char lastChar = '\0';
    
    // Nuevo: contador y límite de iteraciones
    size_t iterationCount = 0;
    const size_t MAX_ITERATIONS = 1000000; // Ajusta este valor según tus necesidades
    
    while (pos < sourceCode.length() && braceCount > 0 && body.length() <= MAX_FUNCTION_SIZE && iterationCount < MAX_ITERATIONS) {
        iterationCount++;
        char c = sourceCode[pos];
        char nextChar = (pos + 1 < sourceCode.length()) ? sourceCode[pos + 1] : '\0';
        
        // Manejar strings y caracteres
        if (!inLineComment && !inBlockComment) {
            if (c == '"' && lastChar != '\\') inString = !inString;
            if (c == '\'' && lastChar != '\\') inChar = !inChar;
        }
        
        // Manejar comentarios
        if (!inString && !inChar) {
            if (c == '/' && nextChar == '/') inLineComment = true;
            else if (c == '/' && nextChar == '*') inBlockComment = true;
            else if (inLineComment && c == '\n') inLineComment = false;
            else if (inBlockComment && c == '*' && nextChar == '/') {
                inBlockComment = false;
                body += c;
                body += nextChar;
                pos += 2;
                continue;
            }
        }
        
        // Contar llaves solo si no estamos en un string, char o comentario
        if (!inString && !inChar && !inLineComment && !inBlockComment) {
            if (c == '{') braceCount++;
            else if (c == '}') braceCount--;
        }
        
        body += c;
        lastChar = c;
        pos++;
    }
    
    if (iterationCount >= MAX_ITERATIONS) {
        std::cerr << "Advertencia: Se alcanzó el máximo de iteraciones en extractFunctionBody." << std::endl;
    }
    
    return body;
}


std::string FunctionExtractor::analyzeComplexity(const std::string& code) {
    try {
        // Limitar la cantidad de código a analizar para evitar tiempos excesivos
        const size_t MAX_ANALYSIS_LENGTH = 10000;
        std::string codeToAnalyze = code.substr(0, std::min(code.size(), MAX_ANALYSIS_LENGTH));
        
        // Detectar nombre de la función actual del código
        std::regex functionNamePattern("(\\w+)\\s*\\([^)]*\\)\\s*\\{");
        std::smatch nameMatch;
        std::string functionName;
        
        if (std::regex_search(codeToAnalyze, nameMatch, functionNamePattern)) {
            functionName = nameMatch[1];
        }

        // Contar estructuras de control
        std::regex loopPattern("\\b(for|while)\\b");
        std::regex ifPattern("\\bif\\b");
        
        // Detectar recursión solo si encontramos el nombre de la función
        bool hasRecursion = false;
        if (!functionName.empty()) {
            std::regex recursivePattern("\\b" + functionName + "\\s*\\([^)]*\\)");
            // Buscar desde después de la declaración de la función
            std::string functionBody = codeToAnalyze.substr(nameMatch.position() + nameMatch.length());
            hasRecursion = std::regex_search(functionBody, recursivePattern);
        }

        // Contar ocurrencias
        auto loops = std::distance(
            std::sregex_iterator(codeToAnalyze.begin(), codeToAnalyze.end(), loopPattern),
            std::sregex_iterator()
        );
        
        auto conditionals = std::distance(
            std::sregex_iterator(codeToAnalyze.begin(), codeToAnalyze.end(), ifPattern),
            std::sregex_iterator()
        );

        // Detectar bucles anidados
        int maxNesting = 0;
        int currentNesting = 0;
        bool inString = false;
        bool inComment = false;
        bool inLineComment = false;
        char lastChar = '\0';

        for (size_t i = 0; i < codeToAnalyze.length(); i++) {
            char c = codeToAnalyze[i];
            
            // Manejar comentarios
            if (!inString && !inComment && !inLineComment && c == '/' && i + 1 < codeToAnalyze.length()) {
                if (codeToAnalyze[i + 1] == '/') {
                    inLineComment = true;
                    i++;
                    continue;
                } else if (codeToAnalyze[i + 1] == '*') {
                    inComment = true;
                    i++;
                    continue;
                }
            }
            
            // Salir de comentarios
            if (inLineComment && c == '\n') {
                inLineComment = false;
                continue;
            }
            if (inComment && lastChar == '*' && c == '/') {
                inComment = false;
                continue;
            }
            
            // Manejar strings
            if (!inComment && !inLineComment && c == '"' && lastChar != '\\') {
                inString = !inString;
            }
            
            // Contar anidamiento
            if (!inString && !inComment && !inLineComment) {
                if (c == '{') {
                    currentNesting++;
                    maxNesting = std::max(maxNesting, currentNesting);
                }
                else if (c == '}') {
                    currentNesting = std::max(0, currentNesting - 1);
                }
            }
            
            lastChar = c;
        }

        // Determinar complejidad
        if (hasRecursion) {
            return "O(2^n)";
        }
        else if (maxNesting > 1) {
            return "O(n^" + std::to_string(maxNesting) + ")";
        }
        else if (loops > 0) {
            return "O(n)";
        }
        else {
            return "O(1)";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error en analyzeComplexity: " << e.what() << std::endl;
        return "O(?)";
    }
}


bool FunctionExtractor::saveToCSV(const std::vector<Function>& functions, const std::string& outputPath) {
    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        return false;
    }
    
    outputFile << "Nombre,Namespace,Tipo de retorno,Parámetros,Complejidad,Es Template,Cualificadores\n";
    
    for (const Function& func : functions) {
        outputFile << func.name << ","
                  << func.namespace_ << ","
                  << func.returnType << ","
                  << "\"" << func.parameters << "\","
                  << func.complexity << ","
                  << (func.isTemplate ? "Sí" : "No") << ","
                  << "\"" << func.qualifiers << "\"\n";
    }
    
    outputFile.close();
    return true;
}

std::map<std::string, ComplexityCategory> FunctionExtractor::categorizarComplejidad(const std::vector<Function>& functions) {
    std::map<std::string, ComplexityCategory> categories;
    
    for (const auto& func : functions) {
        ComplexityCategory cat;
        
        if (func.complexity == "O(1)") {
            cat = {"Constant", "Tiempo constante", 1};
        }
        else if (func.complexity == "O(n)") {
            cat = {"Linear", "Tiempo lineal", 2};
        }
        else if (func.complexity.find("O(n^") != std::string::npos) {
            cat = {"Polynomial", "Tiempo polinomial", 3};
        }
        else if (func.complexity == "O(2^n)") {
            cat = {"Exponential", "Tiempo exponencial", 4};
        }
        else {
            cat = {"Unknown", "Desconocido", 0};
        }
        
        categories[func.name] = cat;
    }
    
    return categories;
}

std::vector<std::string> FunctionExtractor::extractFunctionNames() {
    // Función lambda para extraer nombres
    auto nameExtractor = [](const Function& func) -> std::string {
        return func.name;
    };
    
    std::vector<std::string> names;
    std::transform(currentFunctions.begin(), currentFunctions.end(), 
                  std::back_inserter(names), nameExtractor);
    return names;
}


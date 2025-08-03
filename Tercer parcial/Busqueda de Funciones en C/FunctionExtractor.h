#pragma once 
#include <vector> 
#include <string>
#include <unordered_set>
#include <map>

struct Function {
    std::string name;
    std::string returnType;
    std::string parameters;
    std::string body;
    std::string complexity;
    bool isTemplate;
    std::string templateParams;
    std::string qualifiers;  // const, override, etc.
    std::string namespace_;  // namespace de la función
};


struct ComplexityCategory {
    std::string category;
    std::string description;
    int level;
};

class FunctionExtractor {
public:
    FunctionExtractor();
    std::map<std::string, ComplexityCategory> categorizarComplejidad(const std::vector<Function>& functions);
    std::vector<Function> extractFromFile(const std::string& filePath);
    bool saveToCSV(const std::vector<Function>& functions, const std::string& outputPath);
    std::vector<std::string> extractFunctionNames();
    void clearCurrentFunctions() { currentFunctions.clear(); }

private:
    static const size_t MAX_FUNCTION_SIZE = 50000; // Máximo tamaño de función a analizar
    static const size_t MAX_FUNCTIONS = 1000;
    std::vector<Function> currentFunctions; 
    std::string readFile(const std::string& filePath);
    std::vector<Function> extractFunctions(const std::string& sourceCode);
    std::string analyzeComplexity(const std::string& code);
    std::string extractFunctionBody(const std::string& sourceCode, size_t startPos);
    bool isValidSourceFile(const std::string& filePath);
    bool fileExists(const std::string &filePath);
    std::streamsize getFileSize(const std::string &filePath);
    bool isBinaryFile(const std::string &filePath);
    std::string analyzeBinaryFile(const std::string& filePath);
};
#pragma once
#include <string>
using namespace std;

__declspec(dllexport) int ingresar(char *msj);
__declspec(dllexport) char ingresarLetra(char *msj);
__declspec(dllexport) float ingresarFloat(char *msj);
__declspec(dllexport) string ingresarString(char *msj);
__declspec(dllexport) double ingresarDouble(char *msj);

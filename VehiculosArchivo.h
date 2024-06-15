#pragma once
#include "Vehiculo.h"
class VehiculosArchivo {
private:
    char _nombreArchivo[40];
public:
    VehiculosArchivo();
    VehiculosArchivo(std::string n);
    Vehiculo leerRegistro(int pos);
    int contarRegistros();
    bool guardarRegistro(Vehiculo reg);
    int buscarRegistro(int id);
    bool modificarRegistro(Vehiculo reg, int pos);
};
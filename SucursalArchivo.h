#pragma once
#include <string>
#include "Sucursal.h"

class SucursalArchivo
{
private:
    char _nombreArchivo[40];
public:
    SucursalArchivo();
    SucursalArchivo(std::string n);
    Sucursal leerRegistro(int pos);
    bool sobreescribirRegistro(Sucursal reg, int pos);
    int contarRegistro();
    int buscarPosicion(int id);
    bool guardarRegistro(Sucursal reg);
};

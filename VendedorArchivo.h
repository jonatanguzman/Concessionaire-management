#pragma once
#include "Vendedor.h"

class VendedorArchivo {
private:
    char _nombreArchivo[40];
public:
    VendedorArchivo();
    VendedorArchivo(std::string nombreArchivo);

    Vendedor leerRegistro(int pos);
    int ContarRegistro();
    bool GuardarRegistro(Vendedor registro);
    bool Sobreescribir(int pos, Vendedor reg);
    int BuscarId(int indice);
};

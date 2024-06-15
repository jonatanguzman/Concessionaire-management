#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include "VentasArchivo.h"
using namespace std;

VentasArchivo::VentasArchivo() 
{
    strcpy(_nombreArchivo, "Ventas.dat");
}

VentasArchivo::VentasArchivo(std::string n = "Ventas.dat")
{
    if (n.size() <= 40) {
        strcpy(_nombreArchivo, n.c_str());
    }
    else {
        cout << "Nombre inválido" << endl;
    }

}

string VentasArchivo::getNombreArchivo()
{
    return _nombreArchivo;
}

Venta VentasArchivo::leerVenta(int pos)
{
    Venta reg;
    FILE* p;

    p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, sizeof reg * pos, 0);
    fread(&reg, sizeof reg, 1, p);
    fclose(p);
    return reg;
 
}

int VentasArchivo::contarVentas()
{
    FILE* p;
    p = fopen(_nombreArchivo, "rb");
    if (p == nullptr) return -1;

    fseek(p, 0, 2);
    int tam = ftell(p) / sizeof(Venta);
    fclose(p);
    return tam;
}

bool VentasArchivo::guardarVenta(Venta reg)
{
    FILE* p;
    p = fopen(_nombreArchivo, "ab");
    if (p == nullptr) return false;

    bool result = fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return result;
}

int VentasArchivo::leerUltimoId()
{
    int cantidad = contarVentas();
    int ultimoId = 0;
    Venta reg;

    reg = leerVenta(cantidad-1);
    ultimoId = reg.getIdVenta();
    
    return ultimoId;
}

bool VentasArchivo::sobreescribirVenta(Venta reg, int pos)
{
    FILE* p;
    bool result;
    p = fopen(_nombreArchivo, "rb+");  
    if (p == nullptr) {
        return false;
    }
    fseek(p, sizeof reg * pos, 0); 
    result = fwrite(&reg, sizeof reg, 1, p); //escribo sobre ese registro
    fclose(p);
    
    return result;
} 

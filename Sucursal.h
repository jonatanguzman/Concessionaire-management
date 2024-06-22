#pragma once
#include "Direccion.h"
class Sucursal
{
private:
    int _idSucursal;
    char _nombre[40];
    Direccion _direccion;
    char _telefono[16];
    bool _estado;
public:
    Sucursal();
    Sucursal(int idSucursal, std::string nombre, Direccion direccion, std::string telefono, bool estado);
    int getIdSucursal();
    std::string getNombre();
    Direccion getDireccion();
    std::string getTelefono();
    bool getEstado();
    void setIdSucursal(int s);
    void setNombre(std::string n);
    void setDireccion(Direccion d);
    void setTelefono(std::string t);
    void setEstado(bool e);
    void Mostrar();
    void Cargar();

    int contarDigitos(int num);

    bool validar(int legajo);

};